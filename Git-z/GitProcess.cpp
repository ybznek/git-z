#include "GitProcess.hpp"
#include <QDebug>
#include <QProcessEnvironment>
using namespace gitz;
GitProcess::GitProcess() : tasks(new GitTaskQueue{this}) {}

void GitProcess::runExec(const QStringList &args) {
  qDebug() << "runexec";
  this->onCommand(args.join(' '));
  process.start(executable, args, QProcess::OpenModeFlag::ReadWrite);
}

void GitProcess::addTask(const QStringList &args, tGitCallback cb) { addTask(args, true, cb); }

void GitProcess::addTask(const QStringList &args, bool waitForFinished, tGitCallback cb) {
  tasks->enqueue(args, cb, waitForFinished);
}

GitProcess::~GitProcess() { process.terminate(); }

void GitProcess::setWorkingDirectory(const QString &newDir) { process.setWorkingDirectory(newDir); }

void GitProcess::printBusyMessage(const QString &cmd) { onError("Program is busy, " + cmd + " is ignored."); }

QString GitProcess::blockingReadOutputLine() {
  if (processStream.atEnd()) {
    process.waitForReadyRead();
  }

  return processStream.readLine();
}

void GitProcess::closeWriteChannel() {
  processStream.flush();
  process.closeWriteChannel();
}

void GitProcess::insertProcessEnvironment(const QString &name, const QString &value) {
  QProcessEnvironment env{QProcessEnvironment::systemEnvironment()};
  env.insert(name, value);
  process.setProcessEnvironment(env);
}
