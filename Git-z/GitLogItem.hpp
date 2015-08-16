#ifndef GITLOGITEM_HPP
#define GITLOGITEM_HPP
#include <QStringRef>
#include <QString>
#include "CommitID.hpp"


#define GETTER(name, index)                                                                                  \
  inline const QStringRef &get##name() const { return items[index]; }

namespace gitz {
  class GitLogItem {
    friend class GitLog;

  protected:
    enum { commit, author, subject, _max_items_ };

  public:
    GitLogItem() {}

    GETTER(CommitHash, commit)
//    GETTER(Date, date)
    GETTER(Author,author)
    GETTER(Subject,subject)

    void pack() { ; } // maybe prepare hashes etc

  protected:
    QStringRef items[_max_items_];
  };
}

#undef GETTER

#endif // GITLOGITEM_HPP
