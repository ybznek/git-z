#include "RebaseList.hpp"


void gitz::RebaseList::append(const gitz::RebaseOperation &op, const gitz::CommitID &id) {
  items.push_back(new rebaseItem{id, op});
}

void gitz::RebaseList::append(const gitz::CommitID &id) { append(RebaseOperation::pick, id); }

void gitz::RebaseList::remove(gitz::RebaseList::iterator &i) {
  delete *i;
  items.erase(i);
}

void gitz::RebaseList::remove(const gitz::CommitID &commit) {
  iterator &&it = find(commit);
  this->remove(it);
}

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
  std::swap(*i1, *i2);
}

bool gitz::RebaseList::isExists(gitz::RebaseList::iterator &iterator) { return iterator != items.end(); }

void gitz::RebaseList::clear() { items.clear(); }

gitz::RebaseList::iterator gitz::RebaseList::begin() { return items.begin(); }

gitz::RebaseList::iterator gitz::RebaseList::end() { return items.end(); }

const gitz::RebaseList::const_iterator gitz::RebaseList::begin() const { return items.begin(); }

const gitz::RebaseList::const_iterator gitz::RebaseList::end() const { return items.end(); }

gitz::RebaseList::~RebaseList() {
  for (rebaseItem *itm : items) {
    delete itm;
  }
}


gitz::RebaseList::rebaseItem::rebaseItem(const gitz::CommitID &commit, const gitz::RebaseOperation &op)
    : commit{commit}, op{op} {}
