#ifndef REUSABLELIST_HPP
#define REUSABLELIST_HPP

#include "GitLogItem.hpp"
#include <vector>

namespace gitz {

  template <typename X>
  /**
   * List reuse old memory
   */
  class ReusableList {
  protected:
    using tList = typename std::vector<X>;

  public:
    using Iterator = typename tList::iterator;
    using ConstIterator = typename tList::const_iterator;
    using sizeType = typename tList::size_type;

    ReusableList() {}

    inline void clear() { internalSize = 0; }

    inline void allocate(int length) {
      int diff = length - items.size();
      for (; diff > 0; --diff) {
        items.push_back(X{});
      }
    }

    inline void setSize(int size) {
      int diff = size - internalSize;
      if (diff > 0) {
        allocate(size); // todo optimize
      }
      internalSize = size;
    }
    X &append() {

      if (items.size() > internalSize) {
        return items[internalSize++];
      } else {
        items.push_back(X{});
        ++internalSize;
        return items.back();
      }
    }


    inline sizeType size() const { return internalSize; }

    const X &operator[](int index) const { return items[index]; }
    X &operator[](int index) { return items[index]; }

    inline Iterator begin() { return items.begin(); }
    inline Iterator end() { return items.begin() + internalSize; }

    inline ConstIterator begin() const { return items.cbegin(); }
    inline ConstIterator end() const { return items.cbegin() + internalSize; }


  protected:
    sizeType internalSize = 0;
    tList items;
  };
}

#endif // REUSABLELIST_HPP
