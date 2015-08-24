#include "FileTreeRoot.hpp"
#include <QDebug>
namespace gitz {
  namespace widget {
    FileTreeItem *FileTreeRoot::parent() { return nullptr; }

    int FileTreeRoot::count() const { return QList<FileTreeFolder>::size(); }

    const FileTreeItem *FileTreeRoot::at(int index) const {
      if (index >= size())
        return nullptr;
      return &(QList<FileTreeFolder>::at(index));
    }
  }
}
