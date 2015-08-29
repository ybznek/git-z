#include "GitFileViewModel.hpp"
#include <QModelIndex>
#include <QFont>
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

void widget::GitFileViewModel::assignTreeView(QTreeView *treeView) {
  this->treeView = treeView;
  treeView->setModel(this);
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
    switch (section) {
    case FILENAME_COLUMN:
      return "Filename";
    case STATE_COLUMN:
      return "State";
    default:
      Q_UNREACHABLE();
    }
  return QVariant();
}


QVariant widget::GitFileViewModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid())
    return QVariant();


  FileTreeItem *ptr = static_cast<FileTreeItem *>(index.internalPointer());

  for (FileTreeFile *file = ptr->cast<FileTreeFile>(); file != nullptr;) {

    if (index.column() == FILENAME_COLUMN) {
      switch (role) {
      case Qt::DecorationRole:
        return iconFactory.getIcon(file->getStatus());
      case Qt::DisplayRole:
        return file->getFilename();
      default:
        return QVariant();
      }


    } else {
      if (role != Qt::DisplayRole)
        return QVariant();
      return file->getStringStatus();
    }
  }


  for (FileTreeFolder *folder = ptr->cast<FileTreeFolder>(); folder != nullptr;) {

    if (index.column() == FOLDER_COLUMN) {
      switch (role) {
      case Qt::DisplayRole:
        return folder->getPath();

      case Qt::DecorationRole:
        qDebug() << "decoration";
        return iconFactory.getFolderIcon();

      case Qt::FontRole:
        QFont boldFont;
        boldFont.setBold(true);
        //          boldFont.setWeight(QFont::Weight::Black);
        qDebug() << "font";
        return boldFont;
      }
    }


    return QVariant();
  }

  /*

    for (FileTreeRoot *root = ptr->cast<FileTreeRoot>(); root != nullptr;) {
        if (role == Qt::DisplayRole)
      return "root";
    }*/
  return QVariant();
}

void widget::GitFileViewModel::deleteOld() {
  int folderCount = root.count();
  for (int i = 0; i < folderCount; ++i) {

    FileTreeFolder *folder = static_cast<FileTreeFolder *>(root.at(i));
    int filesCount = folder->count();
    for (int j = 0; j < filesCount; ++j) {
      FileTreeFile *file = static_cast<FileTreeFile *>(folder->at(j));
      qDebug() << file->gitFile.getFilepath();
      if (!file->isValid()) {
        folder->remove(i);
        --filesCount;
        changed = true;
      }
    }
    if (folder->count() == 0) {
      root.remove(i);
      --folderCount;
    }
  }
}


void widget::GitFileViewModel::fileListUpdated() {
  qDebug() << "file list";
  LockHolder<const GitFileList> fileList = git.getFileList();
  invalidate();
  changed = false;
  for (const GitFile &file : fileList) {
    QString path = file.getPath();
    FileTreeFolder &folder = root.getFolder(path);
    if (folder.addFile(file)) {
      changed = true;
    }
  }
  deleteOld();

  if (changed) {
    root.updateRows();
    emit dataChanged(index(0, 0), index(0, root.count() - 1));

    emit treeView->expandAll();
    treeView->resizeColumnToContents(0);
  }
}


void widget::GitFileViewModel::invalidate() {
  for (FileTreeFolder &folder : root) {
    for (FileTreeFile &file : folder.files) {
      file.setValid(false);
    }
  }
}
