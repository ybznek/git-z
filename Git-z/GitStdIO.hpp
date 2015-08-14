#ifndef GITSTDIO_HPP
#define GITSTDIO_HPP

#include <QObject>

#include <QFile>
#include <QTextStream>
#include <iostream>

#include <QDebug>
namespace gitz {
  class GitStdIO : public QObject {
    Q_OBJECT
  public:
    struct endl {};
    GitStdIO() : input{}, inStream{&input} {
      input.open(stdin, QFile::ReadOnly);
      output.open(stdout, QFile::WriteOnly);
    }

    inline GitStdIO &operator<<(const QString &str) {
      output.write(str.toLocal8Bit());
      return *this;
    }
    inline GitStdIO &operator<<(char chr) {
      output.write(&chr, 1);
      return *this;
    }

    inline void flush() { output.flush(); }

    inline bool operator>>(QString &str) {
      str = inStream.readLine();
      return !inStream.atEnd();
    }

  protected:
    QFile input;
    QFile output;
    QTextStream inStream;
  };
}

#endif // GITSTDIO_HPP
