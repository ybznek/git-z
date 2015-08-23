#include "GitFileViewModel.hpp"
#include <QModelIndex>

widget::GitFileViewModel::GitFileViewModel(Git &git) : git{git} {
  QObject::connect(&git, SIGNAL(onStatusUpdated()), this, SLOT(fileListUpdated()));
}


QModelIndex widget::GitFileViewModel::index(int row, int column, const QModelIndex &parent) const {
  qDebug() << "index";
  if (!hasIndex(row, column, parent))
    return QModelIndex();
  void *parentPtr = parent.internalPointer();
  if (!parent.isValid()) {
    if (row >= root.size()) {
      return QModelIndex{};
    }
    const FileTreeFolder *item = &(root.at(row));
    return createIndex(row, column, const_cast<FileTreeFolder *>(item));
  }

  FileTreeItem *item = static_cast<FileTreeItem *>(parentPtr);
  FileTreeFolder *folder;
  if ((folder = dynamic_cast<FileTreeFolder *>(item))) {
    const FileTreeFolder::FileList &files = folder->files;
    if (row >= files.size()) {
      return QModelIndex{};
    }
    return createIndex(row, column, const_cast<FileTreeFile *>(&files.at(row)));
  }
  return QModelIndex{};
}

QModelIndex widget::GitFileViewModel::parent(const QModelIndex &child) const {
  qDebug() << "parent";
  if (!child.isValid()) {
    return QModelIndex{};
  }

  FileTreeItem *childPtr = static_cast<FileTreeItem *>(child.internalPointer());


  const FileTreeItem *parentItem = childPtr->parent();

  if (parentItem == &root) {
    return QModelIndex();
  }

  int row = root.indexOf(*(static_cast<const FileTreeFolder *>(parentItem)));
  return createIndex(row, 0, const_cast<FileTreeItem *>(static_cast<const FileTreeItem *>(parentItem)));
}


int widget::GitFileViewModel::rowCount(const QModelIndex &parent) const {
  qDebug() << "rowCount";
  if (!parent.isValid()) {
      qDebug() << root.count();

    return root.count();
  }
  qDebug() << "valid";
  FileTreeItem *item = static_cast<FileTreeItem *>(parent.internalPointer());
      qDebug() << item->count();
  return item->count();
}

int widget::GitFileViewModel::columnCount(const QModelIndex &parent) const {
  qDebug() << "columnCount";
  return 1;
}


QVariant widget::GitFileViewModel::headerData(int section, Qt::Orientation orientation, int role) const {
  qDebug() << "header";
  return "header";
}

QVariant widget::GitFileViewModel::data(const QModelIndex &index, int role) const {
  qDebug() << "data";
  return "data";
}


void widget::GitFileViewModel::fileListUpdated() {
  qDebug() << "file list";
  invalidate();
  changed = true;
  LockHolder<const GitFileList> fileList = git.getFileList();
  for (const GitFile &file : fileList) {
    QString path = file.getPath();
    FileTreeFolder &folder = geFileTreeFolder(path);
    if (folder.addFile(file)) {
      changed = true;
    }

    /*          QString state;
                switch (file.getState()) {
                case GiFileTreeItem::CREATED:
                  state = "CREATED";
                  break;
                case GiFileTreeItem::MODIFIED:
                  state = "MODIFIED";
                  break;
                case GiFileTreeItem::REMOVED:
                  state = "REMOVED";
                  break;
                case GiFileTreeItem::UNKNOWN:
                  state = "NOBODY KNOWS";
                  break;
                }*/
  }
  qDebug() << root.count();
  for (FileTreeFolder &folder : root) {
    qDebug() << "path" << folder.path;
    for (FileTreeFile &file : folder.files) {
      qDebug() << "." << file.gitTreeFile.getFilename();
    }
  }
  //        if (changed){
  emit dataChanged(index(0, 0), index(0, root.count()));
  //      }
}

widget::FileTreeFolder &widget::GitFileViewModel::geFileTreeFolder(const QString &path) {
  for (FileTreeFolder &folder : root) {
    if (folder.path == path) {
      return folder;
    }
  }
  root.push_back(FileTreeFolder{&root});
  return root.back();
}

void widget::GitFileViewModel::invalidate() {
  for (FileTreeFolder &folder : root) {
    folder.valid = false;
    for (FileTreeFile &file : folder.files) {
      file.valid = false;
    }
  }
}
