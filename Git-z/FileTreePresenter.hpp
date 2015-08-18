#ifndef FILETREEPRESENTER_HPP
#define FILETREEPRESENTER_HPP
#include "Git.hpp"
#include <QTreeWidget>
#include <QObject>
#include <GitFileList.hpp>
namespace gitz{
namespace widget{

class FileTreePresenter:public QObject
{
Q_OBJECT
public:

    FileTreePresenter(::gitz::Git& git, QTreeWidget* tree, QObject* parent = nullptr):QObject{parent},git{git},tree{tree}{
        QObject::connect(&git,SIGNAL(onStatusUpdated()),this,SLOT(fileListUpdated()));
    }

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
        QTreeWidgetItem *item = new QTreeWidgetItem{tree};
        item->setText(0, file.getFilepath());
        tree->addTopLevelItem(item);
      }
    }

protected:

    ::gitz::Git& git;
    QTreeWidget* tree;
    GitFileList fileList;
};

}
}
#endif // FILETREEPRESENTER_HPP
