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
      const QString &getFilename() const;
      int count() const override;
      const QString &getStatus() const {
        switch (gitFile.getState()) {
        case state::CREATED:
          static const QString created{"created"};
          return created;
        default:
          Q_UNREACHABLE();
          static const QString unknown{"unknown"};
          return unknown;
        }
      }
      bool selected;
      bool valid;
      GitFile gitFile;
      FileTreeItem *parentItem;
    };
  }
}

#endif // FILETREEFILE_HPP
