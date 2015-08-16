#ifndef GITPROCESS_HPP
#define GITPROCESS_HPP

#include <QObject>
#include <QProcess>
#include <QTextStream>
#include <QDebug>
#include "common.hpp"

#include "GitFileList.hpp"
#include "GitTaskQueue.hpp"
namespace gitz {
  class GitTaskQueue;

  class GitProcess : public QObject {
    Q_OBJECT
    friend class TaskThread;

  public slots:
    void setWorkingDirectory(const QString &newDir);

  signals:
    void onError(const QString &errorMessage);
    void onCommand(const QString &command);

  protected:
    GitProcess(); // Make class "abstract"
    ~GitProcess();
    void runExec(const QStringList &args);

    void addTask(const QStringList &args, tGitCallback cb = tGitCallback_NONE);
    void addTask(const QStringList &args, bool waitForFinished, tGitCallback cb = tGitCallback_NONE);

    void printBusyMessage(const QString &cmd);

    inline void waitForFinished() { process.waitForFinished(); }
    inline bool isOutputEnd() { return processStream.atEnd(); }
    inline QString readOutputLine() { return processStream.readLine(); }
    inline void writeToProcess(const QString &s) { processStream << s; }
    inline void writeToProcess(char ch) { processStream << ch; }
    inline QString blockingReadOutputLine() {
      if (processStream.atEnd()) {
        process.waitForReadyRead();
      }

      return processStream.readLine();
    }

    inline void setExecutable(const QString &newExec) { executable = newExec; }
    inline QString readErrorOutput() { return QString{process.readAllStandardError()}; }
    inline QString readStandardOutput() { return QString{process.readAllStandardOutput()}; }
    inline void closeWriteChannel() {
      processStream.flush();
      process.closeWriteChannel();
    }
    void insertProcessEnvironment(const QString &name, const QString &value) {
      QProcessEnvironment env{QProcessEnvironment::systemEnvironment()};
      env.insert(name, value);
      process.setProcessEnvironment(env);
    }


  private:
    QString executable{"git"};
    //    QString executable{"/a/projects/C++/Qt/Git-Z/gitProxy/git"};
    QProcess process;
    QTextStream processStream{&process};
    GitTaskQueue *const tasks;
  };
}
#endif // GITPROCESS_HPP
