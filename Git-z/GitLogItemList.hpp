#ifndef GITLOGITEMLIST_HPP
#define GITLOGITEMLIST_HPP
#include "GitLogItem.hpp"
#include "ReusableList.hpp"
namespace gitz {
  using GitLogItemList = generic::ReusableList<GitLogItem>;
}
#endif // GITLOGITEMLIST_HPP
