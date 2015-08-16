#ifndef GITEDIT_HPP
#define GITEDIT_HPP

#include <QObject>
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <GitStdIO.hpp>
#include <QDebug>
#include <GitEdit.hpp>
#include "common.hpp"

namespace gitz {
  class GitEdit : public QObject {
    Q_OBJECT
  public:
    GitEdit(const QString &filename) : file{filename}, fileStream{&file} {}
    void printFile() {
      while (!fileStream.atEnd()) {
        QString line;

        line = fileStream.readLine();
        qDebug() << line;
        stdio << FILE_CHAR << line << '\n';
        stdio.flush();
      }
      stdio << END_FILE_CHAR << '\n';
      stdio.flush();
    }
    int run() {

      if (!file.open(QFile::ReadWrite)) {
        return false;
      }
      printFile();
      file.reset();

      do {
        QString str;
        stdio >> str;
        if (str.startsWith(END_OF_INPUT)) {
          break;
        }
        fileStream << str << '\n';
      } while (true);
      file.resize(file.pos());

      return 0;
    }
  signals:

  protected slots:


  protected:
    QFile file;
    QTextStream fileStream;
    GitStdIO stdio;
  };
}

#endif // GITEDIT_HPP
