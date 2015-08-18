#ifndef GRAPHVIEWWIDGET_HPP
#define GRAPHVIEWWIDGET_HPP
#include <QWidget>
#include <QPainter>
#include <GitLog.hpp>
#include <QPaintEvent>
#include <QBrush>
#include <QColor>
#include <QScrollBar>
#include <QTableView>
#include <QStandardItemModel>
#include "Git.hpp"
#include "LockHolder.hpp"
#include "GraphViewItemDelegate.hpp"
#include "GraphViewModel.hpp"
using namespace gitz;
class GraphViewWidget : public QTableView {
  Q_OBJECT
public:
  GraphViewWidget(QWidget *parent = nullptr) : QTableView{parent} {
    this->setModel(&model);
    this->setShowGrid(false);
    GraphViewItemDelegate *delegate = new GraphViewItemDelegate{this};
    this->setItemDelegateForColumn(0, delegate);
  }

  void setScrollbar(QScrollBar *scrollbar) { this->scrollbar = scrollbar; }

  inline void setGit(Git *git) { model.setGit(git); }

signals:

public slots:
  void onScroll(int scroll) {
    this->scroll = scroll;
    repaint();
    qDebug() << "scrollChanged";
  }
  void notifyDataChanged() {
    model.notifyDataChanged();
    this->repaint();
  }

protected:
  int scroll = 0;
  const QBrush backgroundBrush{QColor{255, 255, 255}};
  QScrollBar *scrollbar = nullptr;
  GraphViewModel model;
};

#endif // GRAPHVIEWWIDGET_HPP
