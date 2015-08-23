#ifndef GRAPHVIEWMODEL_HPP
#define GRAPHVIEWMODEL_HPP

#include <QAbstractTableModel>
#include "Git.hpp"
#include "ReusableList.hpp"
#include "GraphItem.hpp"
namespace gitz {
  namespace widget {
    class GraphViewModel : public QAbstractTableModel {
      Q_OBJECT
    public:
      GraphViewModel(QObject *parent = nullptr);
      int rowCount(const QModelIndex &parent = QModelIndex()) const;

      QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

      int columnCount(const QModelIndex &parent = QModelIndex()) const;
      QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

      void notifyDataChanged();
      void setGit(Git *git);

    protected:
      Git *git;
      ReusableList<GraphItem> list;
    };
  }
}
#endif // GRAPHVIEWMODEL_HPP
