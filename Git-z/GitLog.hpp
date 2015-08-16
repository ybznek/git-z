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
    GitLog();

    void operator<<(const QString &str);

    inline GitLogItemList::Iterator begin() { return items.begin(); }
    inline GitLogItemList::Iterator end() { return items.end(); }

    inline GitLogItemList::ConstIterator begin() const {return items.begin();}
    inline GitLogItemList::ConstIterator end() const {return items.end();}

    inline int length() const {return items.length();}
    inline const GitLogItem& operator[](int index) const {return items[index];}
    inline const QString &getFormat() { return format; }


  protected:
    inline void parseLine(const QString & str, int& lastPos, GitLogItem& item);
    const QString separator = "|@@|";
    const int separator_length = separator.length();
    QString format;
    GitLogItemList items;
  };
}
#endif // GITGRAPH_HPP
