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
      items.clear();
      int lastPos = 0;
      while (true) {
        lastPos = str.indexOf(separator, lastPos);
        if (lastPos == -1)
          break;
        lastPos += separator_length;
        qDebug() << "ITEM";
        GitLogItem &item = items.append();
        parseLine(str,lastPos,item);
      }
    }

    inline void parseLine(const QString & str, int& lastPos, GitLogItem& item) {
        for (int i = 0; i < GitLogItem::_max_items_; ++i) {
          int newPos = str.indexOf(separator, lastPos);
          item.items[i] = str.mid(lastPos, newPos - lastPos );
          lastPos = newPos + separator_length;
        }
        item.pack();
    }

    inline GitLogItemList::Iterator begin() { return items.begin(); }
    inline GitLogItemList::Iterator end() { return items.end(); }

    inline GitLogItemList::ConstIterator begin() const {return items.begin();}
    inline GitLogItemList::ConstIterator end() const {return items.end();}

    inline int length() const {return items.length();}
    inline const GitLogItem& operator[](int index) const {return items[index];}
    inline const QString &getFormat() { return format; }


  protected:
    const QString separator = "|@@|";
    const int separator_length = separator.length();
    QString format;
    GitLogItemList items;
  };
}
#endif // GITGRAPH_HPP
