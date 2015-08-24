#ifndef FILETREEFILE_HPP
#define FILETREEFILE_HPP
#include "../../GitFile.hpp"
#include "FileTreeItem.hpp"
namespace gitz {
  namespace widget {
    using ::gitz::GitFile;
    class FileTreeFolder;
    class FileTreeFile : public FileTreeItem {
    public:
      FileTreeFile(FileTreeItem *parent, const GitFile &file);
      FileTreeItem *parent() override;
      const FileTreeItem *at(int index) const;
      int count() const override;
      bool selected;
      bool valid;
      GitFile gitTreeFile;
      FileTreeItem *parentItem;
    };
  }
}

#endif // FILETREEFILE_HPP
