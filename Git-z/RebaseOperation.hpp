#ifndef REBASEOPERATION_HPP
#define REBASEOPERATION_HPP

#include <QString>

class RebaseOperation {
public:
  enum op { pick, reword, edit, squash, fixup, exec };

  inline RebaseOperation(op v) : val{v} { ; }

  inline RebaseOperation(const QString &strop) : val{stringToOp(strop)} {}

  inline operator const QString() { return opToString(val); }

protected:
  QString opToString(op val);

  op stringToOp(const QString &str);
  op val;
};

#endif // REBASEOPERATION_HPP
