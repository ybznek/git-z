#include "GitProcess.hpp"
#include <QDebug>
#include <QProcessEnvironment>
using namespace gitz;
GitProcess::GitProcess() : tasks(new GitTaskQueue{this}) {}

void GitProcess::runExec(const QStringList &args) {
  qDebug() << "runexec";
  this->onCommand(args.join(' '));
  process.start(executable, args, QProcess::OpenModeFlag::ReadOnly);
}

void GitProcess::addTask(const QStringList &args, tGitCallback cb) { addTask(args, true, cb); }

void GitProcess::addTask(const QStringList &args, bool waitForFinished, tGitCallback cb) {
  tasks->enqueue(args, cb, waitForFinished);
}

GitProcess::~GitProcess() { process.terminate(); }

void GitProcess::setWorkingDirectory(const QString &newDir) { process.setWorkingDirectory(newDir); }

void GitProcess::printBusyMessage(const QString &cmd) { onError("Program is busy, " + cmd + " is ignored."); }
