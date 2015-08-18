#ifndef GRAPHITEM_HPP
#define GRAPHITEM_HPP
#include "ReusableList.hpp"
namespace gitz {
  namespace widget {
    class GraphItem {

    public:
      enum GraphType {
        POINT_DOWN,
        DOWN,
        POINT_LEFT,
        POINT_RIGHT,
      };

      inline GraphType operator[](int index) { return list[index]; }
      inline int length() const { return list.size(); }
      inline void allocate(int length) { list.allocate(length); }

      QString commit;
      QString author;
      QString subject;

    protected:
      generic::ReusableList<GraphType> list;
    };
  }
}
#endif // GRAPHITEM_HPP
