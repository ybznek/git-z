#include "GitLog.hpp"


gitz::GitLog::GitLog() {

  format += separator + GF::commitHash();
  format += separator + GF::authorName();
  format += separator + GF::subject();
  format += separator;
}

void gitz::GitLog::operator<<(const QString &str) {
  qDebug() << "Parsovani logu: " << str;
  items.clear();
  int lastPos = 0;
  while (true) {
    lastPos = str.indexOf(separator, lastPos);
    if (lastPos == -1)
      break;
    lastPos += separator_length;
    qDebug() << "ITEM";
    GitLogItem &item = items.append();
    parseLine(str, lastPos, item);
  }
}

void gitz::GitLog::parseLine(const QString &str, int &lastPos, gitz::GitLogItem &item) {
  for (int i = 0; i < GitLogItem::_max_items_; ++i) {
    int newPos = str.indexOf(separator, lastPos);
    item.items[i] = str.mid(lastPos, newPos - lastPos);
    lastPos = newPos + separator_length;
  }
  item.pack();
}
