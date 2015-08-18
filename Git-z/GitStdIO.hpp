#ifndef GITSTDIO_HPP
#define GITSTDIO_HPP

#include <QObject>

#include <QFile>
#include <QTextStream>
#include <iostream>

#include <QDebug>
namespace gitz {
  namespace editor {
    class GitStdIO : public QObject {
      Q_OBJECT
    public:
      GitStdIO();

      GitStdIO &operator<<(const QString &str);
      GitStdIO &operator<<(char chr);
      bool operator>>(QString &str);

      inline void flush() { output.flush(); }

    protected:
      QFile input;
      QFile output;
      QTextStream inStream;
    };
  }
}

#endif // GITSTDIO_HPP
