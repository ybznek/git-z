#ifndef GITTASKQUEUE_HPP
#define GITTASKQUEUE_HPP
#include <QMutex>
#include <QStringList>
#include <QQueue>
#include <QProcess>
#include "TaskThread.hpp"
#include "common.hpp"

#include "GitProcess.hpp"
#include "TaskItem.hpp"
#include "TaskQueue.hpp"
#include <QObject>
namespace gitz {
  class GitProcess;
  class TaskThread;

  /**
   * TODO optimize
   * maybe use only signal queue
   */
  class GitTaskQueue : public QObject {
    Q_OBJECT
  public:
    GitTaskQueue(GitProcess *git);
    void enqueue(QStringList args, const tGitCallback &cb, bool waitForFinished);
  signals:
    void process();

  protected:
    volatile bool stopped = false;
    TaskQueue queue;
    QMutex mtx{QMutex::Recursive};
    QThread thr;
    GitProcess *const git;
    TaskThread *const taskThread;
  };
}
#endif // GITTASKQUEUE_HPP
