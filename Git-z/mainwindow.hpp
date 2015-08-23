#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "./gitz/Git.hpp"
#include <QStringListModel>
#include "gitz/GitBranchList.hpp"
#include "gitz/RebaseList.hpp"
#include "LogView.hpp"
#include "gitz/widget/GitFileViewModel.hpp"
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
  void focusChanged(QWidget *old, QWidget *now);

  void enable();
  void showLogView();
  void onBranchesUpdated();

  void onCommit();
  void setBranch(QModelIndex, QModelIndex);
  void renameCurrentBranch(QModelIndex, QModelIndex, QVector<int>);
  void newBranch();
  void onRebase();

private:
  Ui::MainWindow *ui = nullptr;
  Git git;
  LogView logView;
  QStringList strlist;
  QStringListModel strlistModel;
  QStringListModel strlistModel2;
  GitFileList fileList;
  GitFileViewModel fileViewModel;
};

#endif // MAINWINDOW_HPP
