#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "Git.hpp"
#include <QStringListModel>
#include <GitBranchList.hpp>
#include <RebaseList.hpp>
#include "LogView.hpp"
#include "FileTreePresenter.hpp"
using namespace gitz;
using namespace gitz::widget;
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

  void enable() { this->setEnabled(true); }
  void showLogView() {
    logView.setVisible(true);
    emit git.getLog();
  }
  void onBranchesUpdated();

  void onCommit();
  void setBranch(QModelIndex, QModelIndex);
  void renameCurrentBranch(QModelIndex, QModelIndex, QVector<int>);
  void newBranch();
  void onRebase() {
    git.interactiveRebase("56fc4247dacb186506ef6902771235c4490bdf3b", [](Git &git, RebaseList &items) {
      qDebug() << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<";
      items.clear();
      items.append("ddcbb8b9497d9d9fff675be29005010d811c8d01");
      for (RebaseList::rebaseItem *item : items) {
        qDebug() << item->commit << "op" << item->op;
      }
    });
  }

private:
  Ui::MainWindow *ui=nullptr;
  Git git;
  LogView logView{git, this};
  QStringList strlist;
  QStringListModel strlistModel;
  QStringListModel strlistModel2;
  GitFileList fileList;
  FileTreePresenter* fileTreePresenter=nullptr;
};

#endif // MAINWINDOW_HPP
