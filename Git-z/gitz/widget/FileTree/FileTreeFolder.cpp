#include "FileTreeFolder.hpp"

namespace gitz {
  namespace widget {
    FileTreeFolder::FileTreeFolder(FileTreeItem *parent, const QString &path)
        : parentItem{parent}, path{path} {}

    bool FileTreeFolder::addFile(const gitz::GitFile &file) {
      for (FileTreeFile &f : files) {
        if (f.gitTreeFile == file) {
          if (f.gitTreeFile.getState() != file.getState()) {
            f.gitTreeFile.setState(file.getState());
            return true;
          }
          return false;
        }
      }

      files.append(FileTreeFile{this, file});
      return true;
    }

    bool FileTreeFolder::operator==(const FileTreeFolder &f) { return this->path == f.path; }

    FileTreeItem *FileTreeFolder::parent() { return parentItem; }

    const FileTreeItem *FileTreeFolder::at(int index) const {
      if (index >= files.size()) {
        return nullptr;
      }
      return &(files.at(index));
    }

    int FileTreeFolder::count() const { return files.size(); }
  }
}
