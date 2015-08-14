#ifndef REBASELIST_HPP
#define REBASELIST_HPP
#include <QObject>

#include <RebaseOperation.hpp>
#include <CommitID.hpp>

#include <vector>
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

    using itemPtr = std::unique_ptr<rebaseItem>;

  protected:
    using itemVector = std::vector<itemPtr>;
    itemVector items;

  public:
    using iterator = itemVector::iterator;
    void append(const RebaseOperation &op, const CommitID &id);
    inline void append(const CommitID &id) { append(RebaseOperation::pick, id); }

    inline void remove(iterator &i) { items.erase(i); }
    inline void remove(const CommitID &commit) {
      iterator &&it = find(commit);
      this->remove(it);
    }

    iterator find(const CommitID &id);
    inline void swap(iterator &i1, iterator &i2);

    inline bool isExists(iterator &iterator) { return iterator != items.end(); }
    inline void clear() { items.clear(); }
    inline iterator begin() { return items.begin(); }
    inline iterator end() { return items.end(); }
  };
}

#endif // REBASELIST_HPP
