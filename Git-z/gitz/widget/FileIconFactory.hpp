#ifndef FILEICONFACTORY_HPP
#define FILEICONFACTORY_HPP
#include "../GitFile.hpp"
#include <QPixmap>
namespace gitz {
  namespace widget {
    using ::gitz::GitFile;
    class FileIconFactory {
    protected:
      using state = GitFile::state;
      enum { FOLDER_INDEX = GitFile::state::_count_ };

    public:
      FileIconFactory(int width = 16, int height = 16) { resize(width, height); }
      void resize(int width, int height) {

        QPixmap pm;
        for (int i = 0; i < (state::_count_ + 1); ++i) {

          switch (static_cast<state>(i)) {
          case state::CREATED:
            pm = QPixmap{":/icons/files/created.svg"};
            break;
          case state::MODIFIED:
            pm = QPixmap{":/icons/files/modified.svg"};
            break;
          case state::REMOVED:
            pm = QPixmap{":/icons/files/removed.svg"};
            break;
          case FOLDER_INDEX:
            pm = QPixmap{":/icons/files/folder.svg"};
            break;
          default:
            pm = QPixmap{":/icons/files/normal.svg"};
            break;
          }
          icons[i] = pm.scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        }
      }
      const QPixmap &getIcon(GitFile::state state) const { return icons[state]; }
      const QPixmap &getFolderIcon() const { return icons[FOLDER_INDEX]; }

    protected:
      QPixmap icons[GitFile::state::_count_ + 1];
    };
  }
}

#endif // FILEICONFACTORY_HPP
