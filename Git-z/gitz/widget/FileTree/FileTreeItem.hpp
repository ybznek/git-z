#ifndef FILETREEITEM_HPP
#define FILETREEITEM_HPP
#include <QList>
#include "../../GitFile.hpp"
#include "FileTreeItem.hpp"

namespace gitz {
  namespace widget {
    using namespace ::gitz;

    struct FileTreeItem {
      virtual FileTreeItem *parent() const = 0;
      virtual int count() const = 0;
      virtual const FileTreeItem *at(int index) const = 0;
      virtual int row() const;
      template <class C> inline C *cast() { return dynamic_cast<C *>(this); }
      template <class C> inline bool is() { return (cast<C>() != nullptr); }
    };
  }
}

#endif // FILETREEITEM_HPP
