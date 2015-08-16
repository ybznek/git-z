#include "GitLogItemList.hpp"


gitz::GitLogItem &gitz::GitLogItemList::append() {
  if (items.length() > internalLength) {
    return items[internalLength++];
  } else {
    prereserve();
    items.append(GitLogItem{});
    ++internalLength;
    return items.back();
  }
}
