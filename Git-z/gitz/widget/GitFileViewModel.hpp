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
#include "FileIconFactory.hpp"
#include <QPixmap>
#include <QTreeView>
using namespace gitz;
namespace gitz {

  namespace widget {
    class GitFileViewModel : public QAbstractItemModel {
      Q_OBJECT
    public:
      enum { FILENAME_COLUMN = 0, STATE_COLUMN = 1, FOLDER_COLUMN = 0 };

      GitFileViewModel(::gitz::Git &git);

      QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;

      QModelIndex parent(const QModelIndex &child) const override;
      void assignTreeView(QTreeView *treeView);
      int rowCount(const QModelIndex &parent = QModelIndex()) const override;
      int columnCount(const QModelIndex &parent = QModelIndex()) const override;
      QVariant headerData(int section, Qt::Orientation orientation,
                          int role = Qt::DisplayRole) const override;

      QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
      void deleteOld();

    public slots:
      void fileListUpdated();


    protected:
      FileIconFactory iconFactory{16, 16};
      FileTreeFolder &geFileTreeFolder(const QString &path);

      void invalidate();

      bool changed = false;
      FileTreeRoot root;
      QMutex mtx;
      Git &git;
      QTreeView *treeView;
    };
  }
}
#endif // GIFileTreeItemVIEWMODEL_HPP
