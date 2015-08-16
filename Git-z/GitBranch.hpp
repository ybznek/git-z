#ifndef GITBRANCH_HPP
#define GITBRANCH_HPP
#include <QString>

namespace gitz {

  class GitBranch {
  public:
    GitBranch() {}

    GitBranch(QString name) : name{name} {}

    const QString &getName() const { return name; }

  protected:
    QString name;
  };
}
#endif // GITBRANCH_HPP
