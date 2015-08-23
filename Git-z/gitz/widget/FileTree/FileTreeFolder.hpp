#ifndef FILETREEFOLDER_HPP
#define FILETREEFOLDER_HPP
#include <QList>
#include "FileTreeItem.hpp"
#include "FileTreeFile.hpp"

namespace gitz {
  namespace widget {

    class FileTreeFolder : public FileTreeItem {

    public:
      using FileList = QList<FileTreeFile>;
      FileTreeFolder(FileTreeItem *parent);

      bool addFile(const GitFile &file);

      bool operator==(const FileTreeFolder &f);
      FileTreeItem *parent() override;
      int count() const override;
      FileTreeItem *parentItem;
      QString path;
      bool valid;
      FileList files;
    };
  }
}
#endif // FILETREEFOLDER_HPP
