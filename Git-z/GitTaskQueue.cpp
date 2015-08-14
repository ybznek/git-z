#include "GitTaskQueue.hpp"
using namespace gitz;
GitTaskQueue::GitTaskQueue(GitProcess *git) : git{git}, taskThread{new TaskThread{git, queue, mtx}} {
  taskThread->connect(this, SIGNAL(process()), SLOT(process()));
  taskThread->moveToThread(&thr);
  thr.start();
}

void GitTaskQueue::enqueue(QStringList args, const tGitCallback &cb, bool waitForFinished) {
  QMutexLocker locker{&mtx};
  queue.append(TaskItem{args, cb, waitForFinished}); // TODO optimize - do not enque if queue is empty
  emit this->process();
}
