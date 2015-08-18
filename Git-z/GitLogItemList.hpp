#ifndef GITLOGITEMLIST_HPP
#define GITLOGITEMLIST_HPP
#include "GitLogItem.hpp"
#include "ReusableList.hpp"
namespace gitz {
  using GitLogItemList = ReusableList<GitLogItem>;
}
#endif // GITLOGITEMLIST_HPP
