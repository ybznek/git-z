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

      GraphType operator[](int index);
      int length() const;
      void allocate(int length);

      QString commit;
      QString author;
      QString subject;

    protected:
      generic::ReusableList<GraphType> list;
    };
  }
}
#endif // GRAPHITEM_HPP
