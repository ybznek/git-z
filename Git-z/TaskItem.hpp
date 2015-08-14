#ifndef TASKITEM_HPP
#define TASKITEM_HPP
#include "common.hpp"
#include <QStringList>
namespace gitz {
  struct TaskItem {
    inline TaskItem(const QStringList &args, const tGitCallback &cb, bool waitForFinished = true)
        : args{args}, cb{cb}, waitForFinished{waitForFinished} {}
    QStringList args;
    tGitCallback cb;
    bool waitForFinished;
  };
}
#endif // TASKITEM_HPP
