#include "GraphViewWidget.hpp"


gitz::widget::GraphViewWidget::GraphViewWidget(QWidget *parent) : QTableView{parent} {
  this->setModel(&model);
  this->setShowGrid(false);
  GraphViewItemDelegate *delegate = new GraphViewItemDelegate{this};
  this->setItemDelegateForColumn(0, delegate);
}

void gitz::widget::GraphViewWidget::setScrollbar(QScrollBar *scrollbar) { this->scrollbar = scrollbar; }

void gitz::widget::GraphViewWidget::setGit(gitz::Git *git) { model.setGit(git); }

void gitz::widget::GraphViewWidget::onScroll(int scroll) {
  this->scroll = scroll;
  repaint();
  qDebug() << "scrollChanged";
}

void gitz::widget::GraphViewWidget::notifyDataChanged() {
  model.notifyDataChanged();
  this->repaint();
}
