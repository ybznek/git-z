#ifndef GITFILEVIEWMODEL_HPP
#define GITFILEVIEWMODEL_HPP
#include <QAbstractItemModel>
#include "Git.hpp"
#include "GitFileList.hpp"
#include <QMutex>
#include <QMutexLocker>
#include <QList>
using namespace gitz;
namespace gitz {

  namespace widget {
    class GitFileViewModel : public QAbstractItemModel {
      Q_OBJECT
    protected:
      struct tFile {
        tFile(const GitFile &file) : selected{false}, valid{true}, gitFile{file} {}
        bool selected;
        bool valid;
        GitFile gitFile;
      };

      struct tFolder {
        QString path;
        bool valid;
        QList<tFile> files;

        void addFile(const GitFile &file) {
          for (tFile &f : files) {
            if (f.gitFile == file) {
              f.gitFile.setState(file.getState());
              return;
            }
          }

          files.append(tFile{file});
        }
      };


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
        invalidate();
        LockHolder<const GitFileList> fileList = git.getFileList();
        for (const GitFile &file : fileList) {
          QString path = file.getPath();
          tFolder &folder = getFolder(path);
          folder.addFile(file);

          /*          QString state;
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
                    }*/
        }
      }


    protected:
      tFolder &getFolder(const QString &path) {
        for (tFolder &folder : folders) {
          if (folder.path == path) {
            return folder;
          }
        }
        folders.push_back(tFolder{});
        return folders.back();
      }

      void invalidate() {
        for (tFolder &folder : folders) {
          folder.valid = false;
          for (tFile &file : folder.files) {
            file.valid = false;
          }
        }
      }


      QList<tFolder> folders;
      QMutex mtx;
      Git &git;
    };
  }
}
#endif // GITFILEVIEWMODEL_HPP
