#include "RebaseOperation.hpp"

#define NAME_TO_STR(name)                                                                                    \
  case name: {                                                                                               \
    static const QString str{#name};                                                                         \
    return str;                                                                                              \
  }

#define STR_TO_NAME(name)                                                                                    \
  if (str == #name)                                                                                          \
    return name;

gitz::RebaseOperation::RebaseOperation(gitz::RebaseOperation::op v) : val{v} { ; }

gitz::RebaseOperation::RebaseOperation(const QString &strop) : val{stringToOp(strop)} {}

gitz::RebaseOperation &gitz::RebaseOperation::operator=(gitz::RebaseOperation::op newop) {
  val = newop;
  return *this;
}

bool gitz::RebaseOperation::operator==(gitz::RebaseOperation::op v) { return val == v; }

gitz::RebaseOperation &gitz::RebaseOperation::operator=(const QString &strop) {
  val = stringToOp(strop);
  return *this;
}

gitz::RebaseOperation::operator const QString &() const { return opToString(val); }

const QString &gitz::RebaseOperation::opToString(op val) const {
  switch (val) {
    NAME_TO_STR(pick);
    NAME_TO_STR(reword);
    NAME_TO_STR(edit);
    NAME_TO_STR(squash);
    NAME_TO_STR(fixup);
    NAME_TO_STR(exec);
  }
  Q_UNREACHABLE();
}

gitz::RebaseOperation::op gitz::RebaseOperation::stringToOp(const QString &str) const {

  STR_TO_NAME(pick);
  STR_TO_NAME(reword);
  STR_TO_NAME(edit);
  STR_TO_NAME(squash);
  STR_TO_NAME(fixup);
  STR_TO_NAME(exec);

  Q_UNREACHABLE();
}
