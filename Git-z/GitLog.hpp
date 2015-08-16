#ifndef GITGRAPH_HPP
#define GITGRAPH_HPP

#include <QString>
#include "GitLogFormat.hpp"
#include <QDebug>
#include "GitLogItemList.hpp"
#include "GitLogItem.hpp"
#include <QObject>
namespace gitz {

  class GitLog{

  protected:
    using GF = GitLogFormat;

  public:
    GitLog(){

      format += separator + GF::commitHash();
      format += separator + GF::authorName();
      format += separator + GF::subject();
      format += separator;
    }


    void operator<<(const QString &str) {
        qDebug() << "Parsovani logu: " << str;
      data = str;
      items.clear();
      while (true) {
        int lastPos = data.indexOf(separator, lastPos);
        if (lastPos == -1)
          break;
        lastPos += separator_length;
        qDebug() << "ITEM";
        GitLogItem &item = items.append();
        for (int i = 0; i < GitLogItem::_max_items_; ++i) {
          int newPos = data.indexOf(separator, lastPos);
          QStringRef str = data.midRef(lastPos, newPos - lastPos );
          qDebug() << str;
          item.items[i] = str;
          lastPos = newPos + separator_length;
        }

        item.pack();
      }
    }

    inline GitLogItemList::Iterator begin() { return items.begin(); }
    inline GitLogItemList::Iterator end() { return items.end(); }

    inline GitLogItemList::ConstIterator begin() const {return items.begin();}
    inline GitLogItemList::ConstIterator end() const {return items.end();}

    const QString &getFormat() { return format; }

  protected:
    const QString separator = "\x01\x02\x03";
    const int separator_length = separator.length();
    QString format;
    QString data;
    GitLogItemList items;
  };
}
#endif // GITGRAPH_HPP
