#include "GitFile.hpp"


gitz::GitFile::GitFile() {}

gitz::GitFile::GitFile(QString filePath, gitz::GitFile::state s) : s{s}, filePath{filePath} {
  QFileInfo info{filePath};
  fileName = info.fileName();
  path = info.path();
}

gitz::GitFile::state gitz::GitFile::getState() const { return s; }

bool gitz::GitFile::operator==(const gitz::GitFile &f) const { return (f.filePath == filePath); }

void gitz::GitFile::setState(gitz::GitFile::state newState) { s = newState; }

const QString &gitz::GitFile::getFilepath() const { return filePath; }

const QString &gitz::GitFile::getFilename() const { return fileName; }

const QString &gitz::GitFile::getPath() const { return path; }
