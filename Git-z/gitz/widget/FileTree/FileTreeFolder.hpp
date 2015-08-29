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
      FileTreeFolder(FileTreeItem *parent, const QString &path);

      bool addFile(const GitFile &file);
        void remove(int index) override;
      bool operator==(const FileTreeFolder &f);
      FileTreeItem *parent() const override;
      const FileTreeItem *at(int index) const;
      FileTreeItem *at(int index);
      int count() const override;
      const QString &getPath() const;
      FileTreeItem *parentItem;
      QString path;
      FileList files;
    };
  }
}
#endif // FILETREEFOLDER_HPP
