#ifndef GITBRANCHLIST_HPP
#define GITBRANCHLIST_HPP
#include <QVector>
#include "GitBranch.hpp"
namespace gitz {
  class GitBranchList : public QVector<GitBranch> {
  public:
    inline void setSelected(int selected) { this->selected = selected; }
    inline int getSelected() const { return selected; }

  protected:
    int selected = -1;
  };
}
#endif // GITBRANCHLIST_HPP
