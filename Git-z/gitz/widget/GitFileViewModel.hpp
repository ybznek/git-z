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

      bool hasIndex(int row, int column, const QModelIndex &parent) const;
      QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;

      QModelIndex parent(const QModelIndex &child) const;

      QModelIndex sibling(int row, int column, const QModelIndex &idx) const;
      int rowCount(const QModelIndex &parent = QModelIndex()) const;
      int columnCount(const QModelIndex &parent = QModelIndex()) const;
      bool hasChildren(const QModelIndex &parent = QModelIndex()) const;

      QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

      QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

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
