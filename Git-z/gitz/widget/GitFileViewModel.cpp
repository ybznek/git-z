#include "GitFileViewModel.hpp"
#include <QModelIndex>

widget::GitFileViewModel::GitFileViewModel(Git &git) : git{git} {
  QObject::connect(&git, SIGNAL(onStatusUpdated()), this, SLOT(fileListUpdated()));
}


QModelIndex widget::GitFileViewModel::index(int row, int column, const QModelIndex &parent) const {

  qDebug() << "index" << row << column;
  if (!hasIndex(row, column, parent))
    return QModelIndex();


  bool isValid = parent.isValid();
  const FileTreeItem *parentItem = !isValid ? &root : static_cast<FileTreeItem *>(parent.internalPointer());

  const FileTreeItem *childItem = parentItem->at(row);

  if (childItem != nullptr)
    return createIndex(row, column, const_cast<FileTreeItem *>(childItem));
  else
    return QModelIndex();
}

QModelIndex widget::GitFileViewModel::parent(const QModelIndex &index) const {
  if (!index.isValid())
    return QModelIndex();
  FileTreeItem *childItem = static_cast<FileTreeItem *>(index.internalPointer());

  if (childItem == nullptr)
    return QModelIndex();
  FileTreeItem *parentItem = childItem->parent();

  if (parentItem == nullptr)
    return QModelIndex();

  return createIndex(parentItem->row(), 0, parentItem);
}


int widget::GitFileViewModel::rowCount(const QModelIndex &parent) const {
  if (!parent.isValid()) {
    return root.count();
  }
  FileTreeItem *item = static_cast<FileTreeItem *>(parent.internalPointer());
  return item->count();
}

int widget::GitFileViewModel::columnCount(const QModelIndex &parent) const {
  if (!parent.isValid()) {
    return 2;
  }

  FileTreeItem *item = static_cast<FileTreeItem *>(parent.internalPointer());

  if (item->is<FileTreeItem>()) {
    return 2;
  }
  return 1;
}


QVariant widget::GitFileViewModel::headerData(int section, Qt::Orientation orientation, int role) const {
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    return "a";

  return QVariant();
}


QVariant widget::GitFileViewModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid())
    return QVariant();
  if (role != Qt::DisplayRole)
    return QVariant();

  FileTreeItem *ptr = static_cast<FileTreeItem *>(index.internalPointer());

  for (FileTreeFile *file = ptr->cast<FileTreeFile>(); file != nullptr;) {
    if (index.column() == 0) {
      return file->getFilename();
    } else {
      return file->getStatus();
    }
  }

  for (FileTreeFolder *folder = ptr->cast<FileTreeFolder>(); folder != nullptr;) {
    return (index.column() == 0) ? folder->getPath() : QVariant();
  }

  for (FileTreeRoot *root = ptr->cast<FileTreeRoot>(); root != nullptr;) {
    return "root";
  }
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
      qDebug() << "." << file.gitFile.getFilename() << file.count();
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
