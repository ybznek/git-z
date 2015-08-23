#include "FileTreeFile.hpp"


gitz::widget::FileTreeFile::FileTreeFile(const gitz::GitFile &file, gitz::widget::FileTreeItem *parent)
    : selected{false}, valid{true}, giTreeFile{file}, parentItem{parent} {}

gitz::widget::FileTreeItem *gitz::widget::FileTreeFile::parent() { return parentItem; }
