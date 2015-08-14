#include "RebaseList.hpp"


void gitz::RebaseList::append(const RebaseOperation &op, const gitz::CommitID &id) {
  itemPtr item{new rebaseItem{id, op}};
  items.push_back(std::move(item));
}

gitz::RebaseList::iterator gitz::RebaseList::find(const gitz::CommitID &id) {
  for (iterator i = items.begin(); i != items.end(); i++) {

    rebaseItem *item = i->get();
    if (item->commit == id) {
      return i;
    }
  }
  return items.end();
}

void gitz::RebaseList::swap(gitz::RebaseList::iterator &i1, gitz::RebaseList::iterator &i2) {
  itemPtr *ptr = i1.base();
  itemPtr *ptr2 = i2.base();
  ptr->swap(*ptr2);
}
