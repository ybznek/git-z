#ifndef GRAPHVIEWWIDGET_HPP
#define GRAPHVIEWWIDGET_HPP
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QBrush>
#include <QColor>
#include <QScrollBar>
#include <QTableView>
#include <QStandardItemModel>
#include "../GitLog.hpp"
#include "../Git.hpp"
#include "../LockHolder.hpp"
#include "../GraphViewItemDelegate.hpp"
#include "../GraphViewModel.hpp"
namespace gitz {
  namespace widget {
    class GraphViewWidget : public QTableView {
      Q_OBJECT
    public:
      GraphViewWidget(QWidget *parent = nullptr);

      void setScrollbar(QScrollBar *scrollbar);

      void setGit(Git *git);

    signals:

    public slots:
      void onScroll(int scroll);
      void notifyDataChanged();

    protected:
      int scroll = 0;
      const QBrush backgroundBrush{QColor{255, 255, 255}};
      QScrollBar *scrollbar = nullptr;
      GraphViewModel model;
    };
  }
}

#endif // GRAPHVIEWWIDGET_HPP
