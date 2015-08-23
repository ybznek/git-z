#ifndef TASKITEM_HPP
#define TASKITEM_HPP
#include "common.hpp"
#include <QStringList>
namespace gitz {
  struct TaskItem {
    TaskItem(const QStringList &args, const tGitCallback &cb, bool waitForFinished = true);
    QStringList args;
    tGitCallback cb;
    bool waitForFinished;
  };
}
#endif // TASKITEM_HPP
