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

void GitProcess::waitForFinished() { process.waitForFinished(); }

bool GitProcess::isOutputEnd() { return processStream.atEnd(); }

QString GitProcess::readOutputLine() { return processStream.readLine(); }

void GitProcess::writeToProcess(const QString &s) { processStream << s; }

void GitProcess::writeToProcess(char ch) { processStream << ch; }

QString GitProcess::blockingReadOutputLine() {
  if (processStream.atEnd()) {
    process.waitForReadyRead();
  }

  return processStream.readLine();
}

void GitProcess::setExecutable(const QString &newExec) { executable = newExec; }

QByteArray GitProcess::readErrorOutput() { return process.readAllStandardError(); }

QByteArray GitProcess::readStandardOutput() { return process.readAllStandardOutput(); }

void GitProcess::closeWriteChannel() {
  processStream.flush();
  process.closeWriteChannel();
}

void GitProcess::insertProcessEnvironment(const QString &name, const QString &value) {
  QProcessEnvironment env{QProcessEnvironment::systemEnvironment()};
  env.insert(name, value);
  process.setProcessEnvironment(env);
}
