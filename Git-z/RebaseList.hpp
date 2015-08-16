#ifndef REBASELIST_HPP
#define REBASELIST_HPP
#include <QObject>

#include <RebaseOperation.hpp>
#include <CommitID.hpp>

#include <QList>
#include <memory>
namespace gitz {
  class RebaseList : public QObject {
    Q_OBJECT

  public:
    struct rebaseItem {
      inline rebaseItem(const CommitID &commit, const RebaseOperation &op) : commit{commit}, op{op} {}
      CommitID commit;
      RebaseOperation op;
    };


  protected:
    using itemVector = QList<rebaseItem*>;
    itemVector items;

  public:
    using iterator=itemVector::Iterator;

    inline void append(const RebaseOperation &op, const CommitID &id) {
        items.push_back(new rebaseItem{id, op});
    }
    inline void append(const CommitID &id) { append(RebaseOperation::pick, id); }

    inline void remove(iterator &i) {
        delete *i;
        items.erase(i);
    }
    inline void remove(const CommitID &commit) {
      iterator &&it = find(commit);
      this->remove(it);
    }

    iterator find(const CommitID &id);
    inline void swap(iterator &i1, iterator &i2);

    inline bool isExists(iterator &iterator) { return iterator != items.end(); }
    inline void clear() { items.clear(); }


    inline auto begin() { return items.begin(); }
    inline auto end() { return items.end(); }

    inline const auto begin() const { return items.begin(); }
    inline const auto end() const { return items.end(); }

    ~RebaseList(){
        for(rebaseItem* itm:items){
            delete itm;
        }
    }
    //todo http://blog.cppse.nl/cpp-multiple-iterators-with-traits
    //inline const rebaseItem begin() const {return *(items.at(0).get());}
  };
}

#endif // REBASELIST_HPP
