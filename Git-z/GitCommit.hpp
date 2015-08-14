#ifndef GITCOMMIT_HPP
#define GITCOMMIT_HPP
#include <QString>

class GitCommit {
public:
  GitCommit(QString message, QStringList files, bool amend = false)
      : message{message}, files{files}, amend{amend} {}

protected:
  QString message;
  QStringList files;
  bool amend;
};

#endif // GITCOMMIT_HPP
