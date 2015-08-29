#ifndef LOGMODEL_HPP
#define LOGMODEL_HPP
#include "../GitLogItem.hpp"
#include <QAbstractTableModel>
#include "../Git.hpp"
#include "../GitLogItemList.hpp"
#include "../LockHolder.hpp"
#include <QTableView>
namespace gitz {

  namespace widget {
    using ::gitz::Git;
    class GitLogModel : public QAbstractTableModel {
      Q_OBJECT
    protected:
      using LockedLog = LockHolder<const GitLog>;

    public:
      enum { DATE_COLUMN, AUTHOR_COLUMN, COMMIT_COLUMN, SUBJECT_COLUMN, _max_column_ };
      GitLogModel(Git &git, QObject *parent = nullptr) : QAbstractTableModel{parent}, git{git} {}
      void assignTable(QTableView *table) {
        this->table = table;
        table->setModel(this);
      }
      int rowCount(const QModelIndex &parent = QModelIndex()) const override;

      int columnCount(const QModelIndex &parent = QModelIndex()) const override;

      QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
      QVariant headerData(int section, Qt::Orientation orientation,
                          int role = Qt::DisplayRole) const override;

    public slots:
      void logUpdated();

    protected:
      int size = 0;
      Git &git;
      QTableView *table = nullptr;
    };
  }
}

#endif // LOGMODEL_HPP
