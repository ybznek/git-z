#ifndef FILETREEITEM_HPP
#define FILETREEITEM_HPP
#include <QList>
#include "../../GitFile.hpp"
#include "FileTreeItem.hpp"

namespace gitz {
  namespace widget {
    using namespace ::gitz;

    class FileTreeItem {
    public:
      virtual FileTreeItem *parent() const = 0;
      virtual int count() const = 0;
      virtual const FileTreeItem *at(int index) const = 0;
      virtual FileTreeItem *at(int index) = 0;
      template <class C> inline C *cast() { return dynamic_cast<C *>(this); }
      template <class C> inline bool is() { return (cast<C>() != nullptr); }

      virtual void remove(int index) = 0;

      int row() const;
      void setRow(int row);
      void updateRows();

    protected:
      int _row;
    };
  }
}

#endif // FILETREEITEM_HPP
