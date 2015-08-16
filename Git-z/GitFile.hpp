#ifndef GITFILE_HPP
#define GITFILE_HPP
#include <QString>
namespace gitz {
  class GitFile {
  public:
    enum state { UNKNOWN, MODIFIED, CREATED, REMOVED };
    GitFile() {}
    GitFile(QString filename, state s) : filename{filename}, s{s} {}

    state getState() const { return s; }
    const QString &getFilename() const { return filename; }

  protected:
    QString filename;
    enum state s = UNKNOWN;
  };
}
#endif // GITFILE_HPP
