#include "TaskThread.hpp"
#include <QDebug>

using namespace gitz;
void TaskThread::process() {
  qDebug() << "makam";
  queueMtx->lock();
  if (queue->empty()) {
    queueMtx->unlock();
  } else {
    TaskItem item = queue->dequeue();
    queueMtx->unlock();
    runTask(item);
  }
}

TaskThread::TaskThread(GitProcess *git, TaskQueue &queue, QMutex &queueMtx)
    : git{git}, queue{&queue}, queueMtx{&queueMtx} {
  git->process.setParent(this);
}

void TaskThread::stop() {
  QMutexLocker locker{&waitMtx};
  stopped = true;
  anyTask.wakeOne();
}


void TaskThread::runTask(TaskItem &item) {
  qDebug() << "zpracovavam: " << item.args.at(0);
  git->runExec(item.args);

  if (Q_LIKELY(item.waitForFinished)) {
    git->waitForFinished();
  }

  item.cb();
}
