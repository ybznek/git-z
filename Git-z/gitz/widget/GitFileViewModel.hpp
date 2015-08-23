#ifndef GIFileTreeItemVIEWMODEL_HPP
#define GIFileTreeItemVIEWMODEL_HPP
#include <QAbstractItemModel>
#include <QMutex>
#include <QMutexLocker>
#include <QList>
#include "../Git.hpp"
#include "../GitFileList.hpp"
#include "FileTree/FileTreeFolder.hpp"
#include "FileTree/FileTreeRoot.hpp"
#include "FileTree/FileTreeFile.hpp"
using namespace gitz;
namespace gitz {

  namespace widget {
    class GitFileViewModel : public QAbstractItemModel {
      Q_OBJECT
    protected:
    public:
      GitFileViewModel(::gitz::Git &git);

      QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;

      QModelIndex parent(const QModelIndex &child) const override;

      int rowCount(const QModelIndex &parent = QModelIndex()) const override;
      int columnCount(const QModelIndex &parent = QModelIndex()) const override;
      QVariant headerData(int section, Qt::Orientation orientation,
                          int role = Qt::DisplayRole) const override;

      QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

      Qt::ItemFlags flags(const QModelIndex &index) const override {
        if (!index.isValid())
          return 0;

          return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable
                | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
      }

    public slots:
      void fileListUpdated();


    protected:
      FileTreeFolder &geFileTreeFolder(const QString &path);

      void invalidate();

      bool changed = false;
      FileTreeRoot root;
      QMutex mtx;
      Git &git;
    };
  }
}
#endif // GIFileTreeItemVIEWMODEL_HPP
