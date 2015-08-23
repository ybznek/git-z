#ifndef REBASELIST_HPP
#define REBASELIST_HPP
#include <QObject>

#include "RebaseOperation.hpp"
#include "CommitID.hpp"

#include <QList>
#include <memory>
namespace gitz {
  class RebaseList : public QObject {
    Q_OBJECT

  public:
    struct rebaseItem {
      rebaseItem(const CommitID &commit, const RebaseOperation &op);
      CommitID commit;
      RebaseOperation op;
    };


  protected:
    using itemVector = QList<rebaseItem *>;
    itemVector items;

  public:
    using iterator = itemVector::Iterator;
    using const_iterator = itemVector::ConstIterator;

    void append(const RebaseOperation &op, const CommitID &id);
    void append(const CommitID &id);

    void remove(iterator &i);
    void remove(const CommitID &commit);

    iterator find(const CommitID &id);
    void swap(iterator &i1, iterator &i2);

    bool isExists(iterator &iterator);
    void clear();


    iterator begin();
    iterator end();

    const const_iterator begin() const;
    const const_iterator end() const;

    ~RebaseList();
    // todo http://blog.cppse.nl/cpp-multiple-iterators-with-traits
    //  const rebaseItem begin() const {return *(items.at(0).get());}
  };
}

#endif // REBASELIST_HPP
