#ifndef REBASEOPERATION_HPP
#define REBASEOPERATION_HPP

#include <QString>

class RebaseOperation {
public:
  enum op { pick, reword, edit, squash, fixup, exec };

  inline RebaseOperation(op v) : val{v} { ; }

  inline RebaseOperation(const QString &strop) : val{stringToOp(strop)} {}

  inline operator const QString & () const { return opToString(val); }

  inline RebaseOperation& operator=(const QString & strop){ val=stringToOp(strop); return *this;}

  inline RebaseOperation& operator=(op newop){ val=newop; return *this;}

  inline bool operator==(op v) { return val == v;}

protected:
  const QString & opToString(op val) const;

  op stringToOp(const QString &str) const;
  op val;
};

#endif // REBASEOPERATION_HPP
