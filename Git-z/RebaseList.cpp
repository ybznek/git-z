#include "RebaseList.hpp"




gitz::RebaseList::iterator gitz::RebaseList::find(const gitz::CommitID &id) {
  for (iterator i = items.begin(); i != items.end(); i++) {

    rebaseItem *item = *i;
    if (item->commit == id) {
      return i;
    }
  }
  return items.end();
}

void gitz::RebaseList::swap(gitz::RebaseList::iterator &i1, gitz::RebaseList::iterator &i2) {
        std::swap(*i1,*i2);
}
