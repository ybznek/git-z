#include "GraphViewItemDelegate.hpp"


void gitz::widget::GraphViewItemDelegate::drawDisplay(QPainter *painter, const QStyleOptionViewItem &option,
                                                      const QRect &rect, const QString &text) const {
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
