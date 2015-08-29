#include "FileTreeFile.hpp"
namespace gitz {
  namespace widget {

    FileTreeFile::FileTreeFile(FileTreeItem *parent, const gitz::GitFile &file)
        : selected{false}, valid{true}, gitFile{file}, parentItem{parent} {}

    FileTreeItem *FileTreeFile::parent() const { return parentItem; }

    const FileTreeItem *FileTreeFile::at(int index) const { return nullptr; }

    FileTreeItem *FileTreeFile::at(int index) { return nullptr; }

    const QString &FileTreeFile::getFilename() const { return gitFile.getFilename(); }

    int FileTreeFile::count() const { return 0; }

    const QString &FileTreeFile::getStringStatus() const {
      switch (gitFile.getState()) {
      case state::CREATED:
        static const QString created{"created"};
        return created;
      case state::MODIFIED:
        static const QString modified{"modified"};
        return modified;
      case state::REMOVED:
        static const QString removed{"removed"};
        return removed;
      default:
        // Q_UNREACHABLE();
        static const QString unknown{"unknown"};
        return unknown;
      }
    }

    void FileTreeFile::remove(int index) { ; }

    void FileTreeFile::setValid(bool valid) { this->valid = valid; }
  }
}
