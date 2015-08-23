#ifndef FILETREEITEM_HPP
#define FILETREEITEM_HPP
#include <QList>
#include "../../GitFile.hpp"
#include "FileTreeItem.hpp"

namespace gitz {
  namespace widget {
    using namespace ::gitz;

    struct FileTreeItem {
      virtual FileTreeItem *parent() = 0;
    };
  }
}

#endif // FILETREEITEM_HPP
