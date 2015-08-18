#include "GitStdIO.hpp"

gitz::editor::GitStdIO::GitStdIO() : input{}, inStream{&input} {
  input.open(stdin, QFile::ReadOnly);
  output.open(stdout, QFile::WriteOnly);
}

gitz::editor::GitStdIO &gitz::editor::GitStdIO::operator<<(char chr) {
  output.write(&chr, 1);
  return *this;
}

bool gitz::editor::GitStdIO::operator>>(QString &str) {
  str = inStream.readLine();
  return !inStream.atEnd();
}

gitz::editor::GitStdIO &gitz::editor::GitStdIO::operator<<(const QString &str) {
  output.write(str.toLocal8Bit());
  return *this;
}
