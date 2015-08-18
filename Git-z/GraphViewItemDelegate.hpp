#ifndef GRAPHVIEWITEMDELEGATE_HPP
#define GRAPHVIEWITEMDELEGATE_HPP
#include <QItemDelegate>
#include <QObject>
#include <QPainter>
#include <QDebug>
namespace gitz {
  class GraphViewItemDelegate : public QItemDelegate {
    Q_OBJECT
  public:
    using QItemDelegate::QItemDelegate;
    /*    void paint(QPainter *painter, const QStyleOptionViewItem &option,
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
    */
    virtual void drawDisplay(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect,
                             const QString &text) const {
      const auto r = option.rect;

      int w = r.width();
      int h = r.height();
      painter->setPen(Qt::green);
      //      QModelIndex.
      painter->drawRect(r);
      painter->setFont(QFont("Arial", r.height()));
      qDebug() << r.height() << r.top();
      qDebug() << option.index.data().toString();
      painter->drawText(r.left(), r.top() + r.height(), "ahoj");
      painter->drawLine(r.left(), r.top(), r.right(), r.bottom());
    }
    /*    virtual void drawDecoration(QPainter *painter, const QStyleOptionViewItem &option,
                                    const QRect &rect, const QPixmap &pixmap) const;
        virtual void drawFocus(QPainter *painter, const QStyleOptionViewItem &option,
                               const QRect &rect) const;
        virtual void drawCheck(QPainter *painter, const QStyleOptionViewItem &option,
                               const QRect &rect, Qt::CheckState state) const;
      };*/
  };
}

#endif // GRAPHVIEWITEMDELEGATE_HPP
