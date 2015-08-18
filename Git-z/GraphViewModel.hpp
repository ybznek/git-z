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
      GraphViewModel(QObject *parent = nullptr) : QAbstractTableModel{parent} { ; }
      int rowCount(const QModelIndex &parent = QModelIndex()) const {
        qDebug() << "model vraci" << list.size();
        return list.size();
      }
      int columnCount(const QModelIndex &parent = QModelIndex()) const { return 4; }
      QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const { return "ahoj"; }

      void notifyDataChanged() {
        auto const log = git->getLogView();
        int length = log->length();
        list.setSize(length);

        for (int i = 0; i < length; ++i) {
          GraphItem &it = list[i];
          const GitLogItem &logIt = (*log)[i];
          it.commit = logIt.getCommitHash();
          it.author = logIt.getAuthor();
          it.subject = logIt.getSubject();
        }
        emit dataChanged(this->index(0, 0), this->index(4, length));
      }
      inline void setGit(Git *git) { this->git = git; }

    protected:
      Git *git;
      ReusableList<GraphItem> list;
    };
  }
}
#endif // GRAPHVIEWMODEL_HPP
