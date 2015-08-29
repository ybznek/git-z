#ifndef LOGMODEL_HPP
#define LOGMODEL_HPP
#include "../GitLogItem.hpp"
#include <QAbstractTableModel>
#include "../Git.hpp"
#include "../GitLogItemList.hpp"
#include "../LockHolder.hpp"
namespace gitz {

  namespace widget {
    using ::gitz::Git;
    class GitLogModel : public QAbstractTableModel {
      Q_OBJECT
    protected:
      using LockedLog = LockHolder<const GitLog>;

    public:
      GitLogModel(Git &git, QObject *parent = nullptr) : QAbstractTableModel{parent}, git{git} {}

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
    };
  }
}

#endif // LOGMODEL_HPP
