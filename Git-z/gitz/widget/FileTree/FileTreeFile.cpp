#include "FileTreeFile.hpp"
namespace gitz {
  namespace widget {

    FileTreeFile::FileTreeFile(FileTreeItem *parent, const gitz::GitFile &file)
        : selected{false}, valid{true}, gitTreeFile{file}, parentItem{parent} {}

    FileTreeItem *FileTreeFile::parent() { return parentItem; }

    const FileTreeItem *FileTreeFile::at(int index) const { return nullptr; }

    int FileTreeFile::count() const { return 1; }
  }
}
