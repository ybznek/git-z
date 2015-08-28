#ifndef GITFILE_HPP
#define GITFILE_HPP
#include <QString>
#include <QFileInfo>
namespace gitz {
  class GitFile {
  public:
    enum state { UNKNOWN, MODIFIED, CREATED, REMOVED, _count_ };
    GitFile();
    GitFile(QString filePath, state s);

    state getState() const;
    bool operator==(const GitFile &f) const;
    void setState(state newState);
    const QString &getFilepath() const;
    const QString &getFilename() const;
    const QString &getPath() const;

  protected:
    enum state s = UNKNOWN;
    QString filePath;
    QString fileName;
    QString path;
  };
}
#endif // GITFILE_HPP
