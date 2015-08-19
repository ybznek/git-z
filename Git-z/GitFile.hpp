#ifndef GITFILE_HPP
#define GITFILE_HPP
#include <QString>
#include <QFileInfo>
namespace gitz {
  class GitFile {
  public:
    enum state { UNKNOWN, MODIFIED, CREATED, REMOVED };
    inline GitFile() {}
    GitFile(QString filePath, state s) : s{s}, filePath{filePath} {
      QFileInfo info{filePath};
      fileName = info.fileName();
      path = info.path();
    }

    inline state getState() const { return s; }
    inline bool operator==(const GitFile &f) const { return (f.filePath == filePath); }
    inline void setState(state newState) { s = newState; }
    inline const QString &getFilepath() const { return filePath; }
    inline const QString &getFilename() const { return fileName; }
    inline const QString &getPath() const { return path; }

  protected:
    enum state s = UNKNOWN;
    QString filePath;
    QString fileName;
    QString path;
  };
}
#endif // GITFILE_HPP
