#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "Git.hpp"
#include <QStringListModel>
#include <GitBranchList.hpp>
#include <RebaseList.hpp>
using namespace gitz;
namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(const QString &executable, QWidget *parent = nullptr);

  ~MainWindow();

protected slots:
  void focusChanged(QWidget *old, QWidget *now) {
    Q_UNUSED(now);
    if (old == nullptr) {
      emit git.getIndex();
      emit git.getBranches();
    }
  }
  void onBranchesUpdated(const GitBranchList &branchList);
  void fileListUpdated(const GitFileList &fileList);
  void onCommit();
  void setBranch(QModelIndex, QModelIndex);
  void renameCurrentBranch(QModelIndex, QModelIndex, QVector<int>);
  void newBranch();
  void onRebase() {
    git.interactiveRebase("2d0a0daca1a24d4a6a7ad9a1f7127593f69a84a9^1", [](Git &git, RebaseList &items) {
      qDebug() << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<";
      for (RebaseList::itemPtr &itemPtr : items) {
        RebaseList::rebaseItem *item = itemPtr.get();
        qDebug() << item->commit << "op" << item->op;
      }
    });
  }

private:
  Ui::MainWindow *ui;
  Git git;
  QStringList strlist;
  QStringListModel strlistModel;
  QStringListModel strlistModel2;
  GitFileList fileList;
};

#endif // MAINWINDOW_HPP
