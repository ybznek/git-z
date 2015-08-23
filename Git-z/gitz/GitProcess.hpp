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

    void waitForFinished();
    bool isOutputEnd();
    QString readOutputLine();
    void writeToProcess(const QString &s);
    void writeToProcess(char ch);
    QString blockingReadOutputLine();

    void setExecutable(const QString &newExec);
    QByteArray readErrorOutput();
    QByteArray readStandardOutput();
    void closeWriteChannel();
    void insertProcessEnvironment(const QString &name, const QString &value);


  private:
    QString executable{"git"};
    //    QString executable{"/a/projects/C++/Qt/Git-Z/gitProxy/git"};
    QProcess process;
    QTextStream processStream{&process};
    GitTaskQueue *const tasks;
  };
}
#endif // GITPROCESS_HPP
