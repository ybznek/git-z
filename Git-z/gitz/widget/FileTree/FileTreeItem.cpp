#include "FileTreeItem.hpp"

int gitz::widget::FileTreeItem::row() const {
  FileTreeItem *p = parent();
  if (p == nullptr) {
    return -1;
  }
  for (int i = count() - 1; i >= 0; --i) {
    if (p->at(i) == this) {
      return i;
    }
  }
  Q_UNREACHABLE();
  return -1;
}
