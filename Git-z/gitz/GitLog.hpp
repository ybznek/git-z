#ifndef GITGRAPH_HPP
#define GITGRAPH_HPP

#include <QString>
#include <QDebug>
#include <QObject>
#include "GitLogFormat.hpp"
#include "GitLogItemList.hpp"
#include "GitLogItem.hpp"
namespace gitz {

  class GitLog {

  protected:
    using GF = GitLogFormat;

  public:
    GitLog();

    void operator<<(const QString &str);

    GitLogItemList::Iterator begin() { return items.begin(); }
    GitLogItemList::Iterator end() { return items.end(); }

    GitLogItemList::ConstIterator begin() const { return items.begin(); }
    GitLogItemList::ConstIterator end() const { return items.end(); }

    int length() const;
    const GitLogItem &operator[](int index) const;
    const QString &getFormat();


  protected:
    void parseLine(const QString &str, int &lastPos, GitLogItem &item);
    const QString separator = "|@@|";
    const int separator_length = separator.length();
    QString format;
    GitLogItemList items;
  };
}
#endif // GITGRAPH_HPP
