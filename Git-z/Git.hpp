#ifndef GIT_HPP
#define GIT_HPP
#include "GitLog.hpp"
#include "GitProcess.hpp"
#include <QObject>
#include "GitFileList.hpp"
#include "GitBranchList.hpp"
#include "CommitID.hpp"
#include "RebaseList.hpp"
#include <QMutex>
#include "LockHolder.hpp"
#include "LockableObject.hpp"
namespace gitz {

  class Git : public GitProcess {
    Q_OBJECT

  public:
    Git(const QString &executable) { insertProcessEnvironment("GIT_SEQUENCE_EDITOR", executable + " edit"); }
    using tRebaseCallback = std::function<void(Git &, RebaseList &)>;

    inline LockHolder<const GitLog> getLogView() { return LockHolder<const GitLog>(log.mtx, log.obj); }


  public slots:
    void commit(const QString &message, const QStringList &files, bool amend = false);
    void getIndex();
    void getBranches();
    void setBranch(QString branch);
    void renameCurrentBranch(QString newName);
    void createNewBranch(QString name);
    void interactiveRebase(CommitID commit, tRebaseCallback cb);
    void getLog();

  signals:
    void onBranchesUpdated(const GitBranchList &branchList);
    void onStatusUpdated(const GitFileList &list);
    void onLogUpdated();


  protected:
    void readRebaseList(RebaseList &list);
    void writeRebaseList(RebaseList &list);
    void parseStatus();
    QString currentBranch;
    LockableObject<GitLog> log;
    QMutex logMtx;
  };
}
#endif // GIT_HPP
