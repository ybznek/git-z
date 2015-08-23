#include "FileTreeRoot.hpp"


gitz::widget::FileTreeItem *gitz::widget::FileTreeRoot::parent() { return static_cast<FileTreeItem *>(this); }

int gitz::widget::FileTreeRoot::count() const { return QList<FileTreeFolder>::size(); }
