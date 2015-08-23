#ifndef GITBRANCHLIST_HPP
#define GITBRANCHLIST_HPP
#include <QVector>
#include "GitBranch.hpp"

namespace gitz {

  class GitBranchList : public QVector<GitBranch> {
  public:
    void setSelected(int selected);
    int getSelected() const;

  protected:
    int selected = -1;
  };
}
#endif // GITBRANCHLIST_HPP
