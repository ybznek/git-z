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
using namespace gitz;
class GraphViewWidget : public QTableView {
  Q_OBJECT
public:
  explicit GraphViewWidget(QWidget *parent = nullptr) : QTableView{parent} {
    this->setModel(&model);
    this->setShowGrid(false);
    GraphViewItemDelegate *delegate = new GraphViewItemDelegate{this};
    this->setItemDelegateForColumn(0, delegate);
  }

  void setScrollbar(QScrollBar *scrollbar) { this->scrollbar = scrollbar; }

  inline void setGit(Git &git) { this->git = &git; }
/*    void paintEvent(QPaintEvent* event) override
    {
//QTableView::paintEvent(event);
        qDebug() << "top" << event->region().boundingRect().top();;
        QPainter p{this};
        p.setBackground(backgroundBrush);
        p.fillRect(this->geometry(),backgroundBrush);
        int w=this->geometry().width();
        int h=this->geometry().height();
        p.setPen(Qt::green);
        p.drawLine(0,0,w,h);
        qDebug() << "scroll" << scroll << "len" << log->length();
        int length=log->length();
        int pos=0;
        int lineHeight=15;
        p.setFont(QFont("arial",lineHeight-2));
        for (int i=scroll;i<length;++i){
            ++pos;
               const GitLogItem& it = (*log)[i];
                p.drawText(20,lineHeight*pos, it.getCommitHash());
                qDebug() << it.getCommitHash();

        }
}
*/
signals:

public slots:
  void onScroll(int scroll) {
    this->scroll = scroll;
    repaint();
    qDebug() << "scrollChanged";
  }
  void notifyDataChanged() {
    auto const log = git->getLogView();
    resizeTable(log->length());
    int row = 0;
    for (const GitLogItem &logItem : log) {
      model.item(row, 0)->setText(logItem.getSubject());
      model.item(row, 1)->setText(logItem.getCommitHash());
      model.item(row, 2)->setText(logItem.getAuthor());
      ++row;
    }
    //        repaint();
  }

protected:
  void resizeTable(int newLength) { // todo mayby inserting items into begin of table is not effective
    int length = model.rowCount();
    int diff = newLength - length;
    if (diff > 0) {
      model.insertRows(0, diff);
      for (int row = 0; row < diff; ++row) {
        for (int column = 0; column < 3; ++column) {
          model.setItem(row, column, new QStandardItem{});
        }
      }
    } else if (newLength < length) {
      model.removeRows(0, -diff);
    }
  }
  int scroll = 0;
  Git *git = nullptr;
  const QBrush backgroundBrush{QColor{255, 255, 255}};
  QScrollBar *scrollbar = nullptr;
  QStandardItemModel model;
};

#endif // GRAPHVIEWWIDGET_HPP
