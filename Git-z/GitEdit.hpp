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
int run() ;

    void printFile();
  protected:
    QFile file;
    QTextStream fileStream;
    GitStdIO stdio;
  };
}

#endif // GITEDIT_HPP
