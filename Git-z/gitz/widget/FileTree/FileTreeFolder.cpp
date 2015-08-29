#include "FileTreeFolder.hpp"

namespace gitz {
  namespace widget {
    FileTreeFolder::FileTreeFolder(FileTreeItem *parent, const QString &path)
        : parentItem{parent}, path{path} {}

    bool FileTreeFolder::addFile(const gitz::GitFile &file) {
      for (FileTreeFile &f : files) {
        if (f.gitFile == file) {
          if (f.gitFile.getState() != file.getState()) {
            f.gitFile.setState(file.getState());
            f.setValid(true);
            return true;
          }
          return false;
        }
      }

      files.append(FileTreeFile{this, file});
      return true;
    }

    void FileTreeFolder::remove(int index) {
        files.removeAt(index);
    }

    bool FileTreeFolder::operator==(const FileTreeFolder &f) { return this->path == f.path; }

    FileTreeItem *FileTreeFolder::parent() const { return parentItem; }

    const FileTreeItem *FileTreeFolder::at(int index) const {
      if (index >= files.size()) {
        return nullptr;
      }
      return &(files.at(index));
    }

    FileTreeItem *FileTreeFolder::at(int index) {
      if (index >= files.size()) {
        return nullptr;
      }
      return &(files[index]);
    }

    int FileTreeFolder::count() const { return files.size(); }

    const QString &FileTreeFolder::getPath() const { return path; }
  }
}
