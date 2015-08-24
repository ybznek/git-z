#ifndef FILETREEROOT_HPP
#define FILETREEROOT_HPP
#include <QList>
#include "FileTreeItem.hpp"
#include "FileTreeFolder.hpp"
namespace gitz {
  namespace widget {
    class FileTreeRoot : public FileTreeItem, public QList<FileTreeFolder> {
    public:
      FileTreeItem *parent() override;
      int count() const override;
      const FileTreeItem *at(int index) const override;
    };
  }
}

#endif // FILETREEROOT_HPP
