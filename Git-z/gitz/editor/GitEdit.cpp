#include "GitEdit.hpp"


void gitz::editor::GitEdit::printFile() {
  while (!fileStream.atEnd()) {
    QString line;

    line = fileStream.readLine();
    qDebug() << line;
    stdio << FILE_CHAR << line << '\n';
    stdio.flush();
  }
  stdio << END_FILE_CHAR << '\n';
  stdio.flush();
}

gitz::editor::GitEdit::GitEdit(const QString &filename) : file{filename}, fileStream{&file} {}

int gitz::editor::GitEdit::run() {

  if (!file.open(QFile::ReadWrite)) {
    return false;
  }
  printFile();
  file.reset();

  do {
    QString str;
    stdio >> str;
    if (str.startsWith(END_OF_INPUT)) {
      break;
    }
    fileStream << str << '\n';
  } while (true);
  file.resize(file.pos());

  return 0;
}
