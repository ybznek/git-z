#include "GitFileViewModel.hpp"
#include <QModelIndex>

widget::GitFileViewModel::GitFileViewModel(Git &git) : git{git} {
  QObject::connect(&git, SIGNAL(onStatusUpdated()), this, SLOT(fileListUpdated()));
}


QModelIndex widget::GitFileViewModel::index(int row, int column, const QModelIndex &parent) const {
  qDebug() << "index";
  if (!hasIndex(row, column, parent))
    return QModelIndex();

  const FileTreeItem *parentItem;

  if (!parent.isValid())
    parentItem = &root;
  else
    parentItem = static_cast<FileTreeItem *>(parent.internalPointer());

  const FileTreeItem *childItem = parentItem->at(row);
  if (childItem != nullptr)
    return createIndex(row, column, const_cast<FileTreeItem *>(childItem));
  else
    return QModelIndex();
}

QModelIndex widget::GitFileViewModel::parent(const QModelIndex &index) const {
  qDebug() << "parent";
  //  if (!index.isValid())
  //    return QModelIndex();
  qDebug() << "valid";
  FileTreeItem *childItem = static_cast<FileTreeItem *>(index.internalPointer());
  FileTreeItem *parentItem = childItem->parent();

  if (parentItem == &root)
    return QModelIndex();
  qDebug() << "non root";
  return createIndex(0, 0, parentItem);
}


int widget::GitFileViewModel::rowCount(const QModelIndex &parent) const {
  qDebug() << "rowCount";
  return 2;
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
  qDebug() << "col";
  return 2;
  return rowCount(parent);
}


QVariant widget::GitFileViewModel::headerData(int section, Qt::Orientation orientation, int role) const {
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    return "a";

  return QVariant();
}


QVariant widget::GitFileViewModel::data(const QModelIndex &index, int role) const {
  qDebug() << "data";
  if (!index.isValid())
    return QVariant();
  if (role != Qt::DisplayRole)
    return QVariant();
  qDebug() << "data";
  return "data";
}


void widget::GitFileViewModel::fileListUpdated() {
  qDebug() << "file list";
  LockHolder<const GitFileList> fileList = git.getFileList();
  invalidate();
  changed = true;
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
    qDebug() << "path" << folder.path << folder.count();
    for (FileTreeFile &file : folder.files) {
      qDebug() << "." << file.gitTreeFile.getFilename() << file.count();
    }
  }
  //        if (changed){
  emit dataChanged(index(0, 0), index(0, root.count() - 1));
  //      }
}

widget::FileTreeFolder &widget::GitFileViewModel::geFileTreeFolder(const QString &path) {
  for (FileTreeFolder &folder : root) {
    if (folder.path == path) {
      return folder;
    }
  }
  root.push_back(FileTreeFolder{&root, path});
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
