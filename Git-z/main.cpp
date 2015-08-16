#include "mainwindow.hpp"
#include <QApplication>
#include "GitFileList.hpp"
#include <QDebug>
#include <QFile>
#include "GitEdit.hpp"
#include "RebaseList.hpp"
#include "GitLog.hpp"

#define REGISTER_META(name) qRegisterMetaType<name>(#name)

int main(int argc, char *argv[]) {


  QApplication a(argc, argv);

  QStringList args = a.arguments();
  qDebug() << args;
  if ((args.size() == 3) && (args.at(1) == "edit")) {
    QString filename{args.at(2)};
    GitEdit edit{filename};

    return edit.run();

  } else {
    QString executable{args.at(0)};
    MainWindow w{executable};

    REGISTER_META(GitFileList);
    REGISTER_META(GitBranchList);

    QObject::connect(&a, SIGNAL(focusChanged(QWidget *, QWidget *)), &w,
                     SLOT(focusChanged(QWidget *, QWidget *)));
    w.show();
    return a.exec();
  }
}
