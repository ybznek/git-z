#ifndef GITFILEVIEWMODEL_HPP
#define GITFILEVIEWMODEL_HPP
#include <QAbstractItemModel>
#include "Git.hpp"
#include "GitFileList.hpp"
namespace gitz {

  namespace widget {
    class GitFileViewModel : public QAbstractItemModel {
      Q_OBJECT
    public:
      GitFileViewModel(::gitz::Git &git) : git{git} {
        QObject::connect(&git, SIGNAL(onStatusUpdated()), this, SLOT(fileListUpdated()));
      }


      QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const {
        return QModelIndex();
      }
      QModelIndex parent(const QModelIndex &child) const {}

      QModelIndex sibling(int row, int column, const QModelIndex &idx) const { return QModelIndex{}; }
      int rowCount(const QModelIndex &parent = QModelIndex()) const { return 1; }
      int columnCount(const QModelIndex &parent = QModelIndex()) const { return 1; }
      bool hasChildren(const QModelIndex &parent = QModelIndex()) const { return false; }

      QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const {
        return "header";
      }

      QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const { return "a"; }

    public slots:
      void fileListUpdated() {
        qDebug() << "file list";
        this->fileList = *(git.getFileList());
        for (GitFile file : this->fileList) {
          QString state;
          switch (file.getState()) {
          case GitFile::CREATED:
            state = "CREATED";
            break;
          case GitFile::MODIFIED:
            state = "MODIFIED";
            break;
          case GitFile::REMOVED:
            state = "REMOVED";
            break;
          case GitFile::UNKNOWN:
            state = "NOBODY KNOWS";
            break;
          }
        }
      }

    protected:
      struct folder {
        QString folder;
        QList<GitFile> files;
      };

      QList<folder> folders;
      ::gitz::Git &git;
      GitFileList fileList;
    };
  }
}

#endif // GITFILEVIEWMODEL_HPP
