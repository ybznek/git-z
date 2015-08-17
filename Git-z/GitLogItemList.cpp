#include "GitLogItemList.hpp"


gitz::GitLogItem &gitz::GitLogItemList::append() {
  if (items.size() > internalLength) {
    return items[internalLength++];
  } else {
    items.push_back(GitLogItem());
    ++internalLength;
    return items.back();
  }
}
