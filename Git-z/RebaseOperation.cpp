#include "RebaseOperation.hpp"

#define NAME_TO_STR(name)                                                                                    \
  case name:                                                                                                 \
    return #name;
#define STR_TO_NAME(name)                                                                                    \
  if (str == #name)                                                                                          \
    return name;

QString RebaseOperation::opToString(op val) {
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

RebaseOperation::op RebaseOperation::stringToOp(const QString &str) {

  STR_TO_NAME(pick);
  STR_TO_NAME(reword);
  STR_TO_NAME(edit);
  STR_TO_NAME(squash);
  STR_TO_NAME(fixup);
  STR_TO_NAME(exec);

  Q_UNREACHABLE();
}
