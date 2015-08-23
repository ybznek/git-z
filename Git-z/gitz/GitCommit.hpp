#ifndef GITCOMMIT_HPP
#define GITCOMMIT_HPP
#include <QString>
#include <QStringList>
namespace gitz {
  class GitCommit {
  public:
    GitCommit(QString message, QStringList files, bool amend = false);

  protected:
    QString message;
    QStringList files;
    bool amend;
  };
}
#endif // GITCOMMIT_HPP
