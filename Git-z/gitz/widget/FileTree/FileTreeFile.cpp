#include "FileTreeFile.hpp"
namespace gitz {
  namespace widget {

    FileTreeFile::FileTreeFile(FileTreeItem *parent, const gitz::GitFile &file)
        : selected{false}, valid{true}, gitFile{file}, parentItem{parent} {}

    FileTreeItem *FileTreeFile::parent() const { return parentItem; }

    const FileTreeItem *FileTreeFile::at(int index) const { return nullptr; }

    const QString &FileTreeFile::getFilename() const { return gitFile.getFilename(); }

    int FileTreeFile::count() const { return 0; }
  }
}
