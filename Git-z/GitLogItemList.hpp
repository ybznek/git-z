#ifndef GITLOGITEMLIST_HPP
#define GITLOGITEMLIST_HPP
#include "GitLogItem.hpp"
#include <QList>

namespace gitz {
  /**
   * List reuse old memory
   */
  class GitLogItemList {
  protected:
    using tList = QList<GitLogItem>;

  public:
    using Iterator = tList::Iterator;
    using ConstIterator = tList::ConstIterator;

    GitLogItemList() { prereserve(); }

    inline void clear() { internalLength = 0; }

    GitLogItem &append();

    inline int length() const { return internalLength; }

    const GitLogItem &operator[](int index) const { return items[index]; }

    inline Iterator begin() { return items.begin(); }
    inline Iterator end() { return items.begin() + internalLength; }

    inline ConstIterator begin() const { return items.constBegin(); }
    inline ConstIterator end() const { return items.constBegin() + internalLength; }


  protected:
    inline void prereserve() { items.reserve(internalLength + 100); }
    int internalLength = 0;
    tList items;
  };
}

#endif // GITLOGITEMLIST_HPP
