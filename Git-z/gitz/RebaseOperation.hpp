#ifndef REBASEOPERATION_HPP
#define REBASEOPERATION_HPP

#include <QString>
namespace gitz {
  class RebaseOperation {
  public:
    enum op { pick, reword, edit, squash, fixup, exec };

    RebaseOperation(op v);

    RebaseOperation(const QString &strop);

    operator const QString &() const;

    RebaseOperation &operator=(const QString &strop);

    RebaseOperation &operator=(op newop);

    bool operator==(op v);

  protected:
    const QString &opToString(op val) const;

    op stringToOp(const QString &str) const;
    op val;
  };
}
#endif // REBASEOPERATION_HPP
