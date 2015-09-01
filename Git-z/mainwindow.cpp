#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "gitz/GitFile.hpp"
#include <QItemSelectionModel>
#include <QDebug>
#include <QObject>
#include <QTreeWidgetItem>
MainWindow::MainWindow(const QString &executable, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), git{executable}, logView{git}, fileViewModel{git},
      logViewModel{git} {
  ui->setupUi(this);
  fileViewModel.assignTreeView(ui->fileView);
  git.setWorkingDirectory("/home/data/projects/C++/Qt/Git-Z/testingRepository");
  // git.setWorkingDirectory("/home/data/projects/C++/Qt/Git-Z/testingRepositorya");

  logViewModel.assignTable(ui->logTableView);
  logView.setModal(true);


  // Events from git

  QObject::connect(&git, SIGNAL(onError(QString)), ui->logView, SLOT(appendPlainText(QString)));
  QObject::connect(&git, SIGNAL(onError(QString)), ui->logView, SLOT(appendPlainText(QString)));
  QObject::connect(&git, SIGNAL(onCommand(QString)), ui->logView, SLOT(appendPlainText(QString)));
  QObject::connect(&git, SIGNAL(onBranchesUpdated()), this, SLOT(onBranchesUpdated()));

  QObject::connect(&git, SIGNAL(onLogUpdated()), &logViewModel, SLOT(logUpdated()));

  QObject::connect(ui->newBranchEdit, SIGNAL(returnPressed()), this, SLOT(newBranch()));


  // Buttons
  QObject::connect(ui->refreshButton, SIGNAL(clicked(bool)), &git, SLOT(getIndex()));
  QObject::connect(ui->commitButton, SIGNAL(clicked(bool)), this, SLOT(onCommit()));

  QObject::connect(ui->commitMessage, SIGNAL(returnPressed()), this, SLOT(onCommit()));

  QObject::connect(ui->logTableView->selectionModel(),
                   SIGNAL(selectionChanged(QItemSelection, QItemSelection)), this,
                   SLOT(onSelectionChanged(QItemSelection)));
  // logview
  //  emit ui->logViewButton->click();

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

void MainWindow::focusChanged(QWidget *old, QWidget *now) {
  Q_UNUSED(now);
  if (old == nullptr) {
    emit git.getIndex();
    emit git.getBranches();
    emit git.getLog();
  }
}

void MainWindow::enable() { this->setEnabled(true); }

void MainWindow::showLogView() {
  logView.setVisible(true);
  emit git.getLog();
}


void MainWindow::onCommit() {
  qDebug() << "commit";
  QStringList files;
  auto indexes = ui->indexView->selectionModel()->selectedIndexes();
  for (QModelIndex modelIndex : indexes) {
    int index = modelIndex.row();
    files << fileList.at(index).getFilename();
  }

  QPlainTextEdit *edit = ui->commitMessage;
  git.commit(edit->toPlainText(), files);
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

void MainWindow::onRebase() {
  git.interactiveRebase("56fc4247dacb186506ef6902771235c4490bdf3b", [](Git &git, RebaseList &items) {
    qDebug() << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<";
    items.clear();
    items.append("ddcbb8b9497d9d9fff675be29005010d811c8d01");
    for (RebaseList::rebaseItem *item : items) {
      qDebug() << item->commit << "op" << item->op;
    }
  });
}

void MainWindow::onBranchesUpdated() {
  LockHolder<const GitBranchList> branchList = git.getBranchList();
  qDebug() << "mam branche";
  QStringList list;
  QString title = branchList->at(branchList->getSelected()).getName();
  this->setWindowTitle(title);
  for (GitBranch b : branchList) {
    list << b.getName();
  }


  this->strlistModel2.setStringList(list);

  QModelIndex index = ui->branchView->model()->index(branchList->getSelected(), 0);
  ui->branchView->selectionModel()->select(index, QItemSelectionModel::Select);
}
