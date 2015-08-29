#include "FileTreeRoot.hpp"
#include <QDebug>
namespace gitz {
  namespace widget {
    FileTreeItem *FileTreeRoot::parent() const { return nullptr; }

    int FileTreeRoot::count() const { return QList<FileTreeFolder>::size(); }

    const FileTreeItem *FileTreeRoot::at(int index) const {
      if (index >= size())
        return nullptr;
      return &(QList<FileTreeFolder>::at(index));
    }

    FileTreeItem *FileTreeRoot::at(int index) {
      if (index >= size())
        return nullptr;
      return &(QList<FileTreeFolder>::operator[](index));
    }

    void FileTreeRoot::remove(int index) { removeAt(index); }

    FileTreeFolder &FileTreeRoot::getFolder(const QString &path) {
      for (FileTreeFolder &folder : *this) {
        if (folder.path == path) {
          return folder;
        }
      }
      push_back(FileTreeFolder{this, path});
      return back();
    }
  }
}
