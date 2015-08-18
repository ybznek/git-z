#ifndef GITFILE_HPP
#define GITFILE_HPP
#include <QString>
#include <QFileInfo>
namespace gitz {
  class GitFile {
  public:
    enum state { UNKNOWN, MODIFIED, CREATED, REMOVED };
    GitFile() {}
    GitFile(QString filepath, state s) : info{filepath}, s{s} {}

    state getState() const { return s; }
    const QString getFilepath() const { return info.filePath(); }
    const QString getFilename() const { return info.fileName(); }
    const QString getPath() const { return info.path(); }

  protected:
    QFileInfo info;
    enum state s = UNKNOWN;
  };
}
#endif // GITFILE_HPP
