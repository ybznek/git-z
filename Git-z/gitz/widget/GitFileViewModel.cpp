#include "GitFileViewModel.hpp"


widget::GitFileViewModel::GitFileViewModel(Git &git) : git{git} {
  QObject::connect(&git, SIGNAL(onStatusUpdated()), this, SLOT(fileListUpdated()));
}

bool widget::GitFileViewModel::hasIndex(int row, int column, const QModelIndex &parent) const {
  if (row > 5)
    return false;
  if (column > 2)
    return false;
  return true;
}

QModelIndex widget::GitFileViewModel::index(int row, int column, const QModelIndex &parent) const {
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

QModelIndex widget::GitFileViewModel::sibling(int row, int column, const QModelIndex &idx) const {
  return QModelIndex{};
}

int widget::GitFileViewModel::rowCount(const QModelIndex &parent) const { return 1; }

int widget::GitFileViewModel::columnCount(const QModelIndex &parent) const { return 1; }

bool widget::GitFileViewModel::hasChildren(const QModelIndex &parent) const { return true; }

QVariant widget::GitFileViewModel::headerData(int section, Qt::Orientation orientation, int role) const {
  return "header";
}

QVariant widget::GitFileViewModel::data(const QModelIndex &index, int role) const { return "a"; }

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
  //        if (changed){
  emit dataChanged(index(0, 0), index(2, 5));
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
