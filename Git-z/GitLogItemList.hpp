#ifndef GITLOGITEMLIST_HPP
#define GITLOGITEMLIST_HPP
#include "GitLogItem.hpp"
#include <vector>

namespace gitz {
  /**
   * List reuse old memory
   */
  class GitLogItemList {
  protected:
    using tList = std::vector<GitLogItem>;

  public:
    using Iterator = tList::iterator;
    using ConstIterator = tList::const_iterator;
    using sizeType = tList::size_type;

    GitLogItemList() {}

    inline void clear() { internalLength = 0; }

    GitLogItem &append();

    inline sizeType length() const { return internalLength; }

    const GitLogItem &operator[](int index) const { return items[index]; }

    inline Iterator begin() { return items.begin(); }
    inline Iterator end() { return items.begin() + internalLength; }

    inline ConstIterator begin() const { return items.cbegin(); }
    inline ConstIterator end() const { return items.cbegin() + internalLength; }


  protected:
    sizeType internalLength = 0;
    tList items;
  };
}

#endif // GITLOGITEMLIST_HPP
