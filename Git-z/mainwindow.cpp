#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "GitFile.hpp"
#include <QItemSelectionModel>
#include <QDebug>
#include <QObject>
MainWindow::MainWindow(const QString &executable, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), git{executable} {
  ui->setupUi(this);
  git.setWorkingDirectory("/home/data/projects/C++/Qt/Git-Z/testingRepository");

  // Events from git

  QObject::connect(&git, SIGNAL(onError(QString)), ui->logView, SLOT(appendPlainText(QString)));
  QObject::connect(&git, SIGNAL(onError(QString)), ui->logView, SLOT(appendPlainText(QString)));
  QObject::connect(&git, SIGNAL(onCommand(QString)), ui->logView, SLOT(appendPlainText(QString)));
  QObject::connect(&git, SIGNAL(onBranchesUpdated(GitBranchList)), this,
                   SLOT(onBranchesUpdated(GitBranchList)));
  QObject::connect(&git, SIGNAL(onStatusUpdated(GitFileList)), this, SLOT(fileListUpdated(GitFileList)));

  QObject::connect(ui->newBranchEdit, SIGNAL(returnPressed()), this, SLOT(newBranch()));


  // Buttons
  QObject::connect(ui->refreshButton, SIGNAL(clicked(bool)), &git, SLOT(getIndex()));
  QObject::connect(ui->commitButton, SIGNAL(clicked(bool)), this, SLOT(onCommit()));

  QObject::connect(ui->commitMessage, SIGNAL(returnPressed()), this, SLOT(onCommit()));

  QObject::connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(onRebase()));
  QObject::connect(ui->logViewButton, SIGNAL(clicked(bool)), this, SLOT(showLogView()));

  ui->indexView->setModel(&strlistModel);

  ui->branchView->setModel(&strlistModel2);
  QObject::connect(ui->branchView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)),
                   this, SLOT(setBranch(QModelIndex, QModelIndex)));
  QObject::connect(ui->branchView->model(), SIGNAL(dataChanged(QModelIndex, QModelIndex, QVector<int>)), this,
                   SLOT(renameCurrentBranch(QModelIndex, QModelIndex, QVector<int>)));

  git.getBranches();
  git.getIndex();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::fileListUpdated(const GitFileList &fileList) {
  qDebug() << "file list";
  this->fileList = fileList;
  this->strlist.clear();
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
    this->strlist.append("<<" + state + ">>\t" + file.getFilename());
  }
  this->strlistModel.setStringList(this->strlist);
}

void MainWindow::onCommit() {
  qDebug() << "commit";
  QStringList files;
  auto indexes = ui->indexView->selectionModel()->selectedIndexes();
  for (QModelIndex modelIndex : indexes) {
    int index = modelIndex.row();
    files << fileList.at(index).getFilename();
  }

  QLineEdit *edit = ui->commitMessage;
  git.commit(edit->text(), files);
  edit->clear();
}

void MainWindow::setBranch(QModelIndex i, QModelIndex i2) {
  Q_UNUSED(i2);
  qDebug() << "set branch";
  emit git.setBranch(i.data().toString());
}

void MainWindow::renameCurrentBranch(QModelIndex i, QModelIndex i2, QVector<int> v) {
  Q_UNUSED(i);
  Q_UNUSED(v);
  git.renameCurrentBranch(i2.data().toString());
}

void MainWindow::newBranch() {
  QLineEdit *edit = ui->newBranchEdit;
  git.createNewBranch(edit->text());
  edit->clear();
}

void MainWindow::onBranchesUpdated(const GitBranchList &branchList) {
  qDebug() << "mam branche";
  QStringList list;
  QString title = branchList.at(branchList.getSelected()).getName();
  this->setWindowTitle(title);
  for (GitBranch b : branchList) {
    list << b.getName();
  }


  this->strlistModel2.setStringList(list);

  QModelIndex index = ui->branchView->model()->index(branchList.getSelected(), 0);
  ui->branchView->selectionModel()->select(index, QItemSelectionModel::Select);
}
