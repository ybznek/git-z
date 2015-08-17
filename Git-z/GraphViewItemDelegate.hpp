#ifndef GRAPHVIEWITEMDELEGATE_HPP
#define GRAPHVIEWITEMDELEGATE_HPP
#include <QItemDelegate>
#include <QObject>
#include <QPainter>
namespace gitz {
  class GraphViewItemDelegate : public QItemDelegate {
    Q_OBJECT
  public:
    using QItemDelegate::QItemDelegate;
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override {
      const auto r = option.rect;

      int w = r.width();
      int h = r.height();
      painter->setPen(Qt::green);
      //      QModelIndex.
      painter->drawRect(r);
      painter->drawText(r.left(), r.top(), index.data().toString());
      //      painter->drawLine(0, r.top() + h*(index.row()-1), w,r.top()+ h * index.row());
    }
  };
}

#endif // GRAPHVIEWITEMDELEGATE_HPP
