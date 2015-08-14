#ifndef TASKTHREAD_HPP
#define TASKTHREAD_HPP
#include <QThread>
#include <QWaitCondition>

#include "TaskQueue.hpp"
#include "GitTaskQueue.hpp"
#include "GitProcess.hpp"
namespace gitz {
  class GitProcess;
  class TaskThread : public QObject {
    Q_OBJECT
  public:
    TaskThread(GitProcess *git, TaskQueue &queue, QMutex &queueMtx);
    void stop();
  public slots:
    void process();

  protected:
    void runTask(TaskItem &item);
    inline void runTask(const TaskItem &item);
    void runTask(const QStringList &args, const tGitCallback &cb);

    GitProcess *git;
    volatile bool stopped = false;
    TaskQueue *const queue;
    QMutex *const queueMtx;
    QMutex waitMtx;

    QWaitCondition anyTask;
  };
}

#endif // TASKTHREAD_HPP
