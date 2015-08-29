#include "FileTreeItem.hpp"
#include <QDebug>

int gitz::widget::FileTreeItem::row() const { return _row; }

void gitz::widget::FileTreeItem::setRow(int row) { _row = row; }

void gitz::widget::FileTreeItem::updateRows() {
  int rowCount = count();
  for (int i = 0; i < rowCount; ++i) {
    FileTreeItem *item = at(i);
    item->setRow(i);
    item->updateRows();
  }
}
