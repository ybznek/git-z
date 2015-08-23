#include "TaskItem.hpp"


gitz::TaskItem::TaskItem(const QStringList &args, const gitz::tGitCallback &cb, bool waitForFinished)
    : args{args}, cb{cb}, waitForFinished{waitForFinished} {}
