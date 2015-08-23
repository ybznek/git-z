#include "FileTreeFolder.hpp"


gitz::widget::FileTreeFolder::FileTreeFolder(gitz::widget::FileTreeItem *parent) : parentItem{parent} {}

bool gitz::widget::FileTreeFolder::addFile(const gitz::GitFile &file) {
  for (FileTreeFile &f : files) {
    if (f.gitTreeFile == file) {
      if (f.gitTreeFile.getState() != file.getState()) {
        f.gitTreeFile.setState(file.getState());
        return true;
      }
      return false;
    }
  }

  files.append(FileTreeFile{file, this});
  return true;
}

bool gitz::widget::FileTreeFolder::operator==(const gitz::widget::FileTreeFolder &f) {
  return this->path == f.path;
}

gitz::widget::FileTreeItem *gitz::widget::FileTreeFolder::parent() { return parentItem; }

int gitz::widget::FileTreeFolder::count() const { return files.size(); }
