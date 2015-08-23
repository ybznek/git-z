#include "FileTreeFile.hpp"


gitz::widget::FileTreeFile::FileTreeFile(const gitz::GitFile &file, gitz::widget::FileTreeItem *parent)
    : selected{false}, valid{true}, gitTreeFile{file}, parentItem{parent} {}

gitz::widget::FileTreeItem *gitz::widget::FileTreeFile::parent() { return parentItem; }

int gitz::widget::FileTreeFile::count() const { return 1; }
