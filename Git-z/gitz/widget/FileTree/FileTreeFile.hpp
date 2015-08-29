#ifndef FILETREEFILE_HPP
#define FILETREEFILE_HPP
#include "../../GitFile.hpp"
#include "FileTreeItem.hpp"
namespace gitz {
  namespace widget {
    using ::gitz::GitFile;
    class FileTreeFolder;
    class FileTreeFile : public FileTreeItem {
    protected:
      using state = GitFile::state;

    public:
      FileTreeFile(FileTreeItem *parent, const GitFile &file);
      FileTreeItem *parent() const override;
      const FileTreeItem *at(int index) const;
      FileTreeItem *at(int index);
      const QString &getFilename() const;
      int count() const override;
      GitFile::state getStatus() const { return gitFile.getState(); }
      const QString &getStringStatus() const;
      void remove(int index) override;
      void setValid(bool valid) { this->valid = true; }
      bool isValid() const { return valid; }
      bool selected;

      GitFile gitFile;
      FileTreeItem *parentItem;

    protected:
      bool valid = true;
    };
  }
}

#endif // FILETREEFILE_HPP
