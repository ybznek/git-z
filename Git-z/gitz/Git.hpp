#ifndef GIT_HPP
#define GIT_HPP
#include <QMutex>
#include <QObject>

#include "GitLog.hpp"
#include "GitProcess.hpp"
#include "GitFileList.hpp"
#include "GitBranchList.hpp"
#include "CommitID.hpp"
#include "RebaseList.hpp"
#include "LockHolder.hpp"
#include "LockableObject.hpp"


#define LOCK_GETTER(type, name, var)                                                                         \
  inline LockHolder<type> get##name() { return LockHolder<type>(var.mtx, var.obj); }

namespace gitz {
  using namespace generic;

  class Git : public GitProcess {
    Q_OBJECT

  public:
    Git(const QString &executable);
    using tRebaseCallback = std::function<void(Git &, RebaseList &)>;


    LOCK_GETTER(const GitLog, GraphLogView, graphLog);
    LOCK_GETTER(const GitLog, LogView, log);
    LOCK_GETTER(const GitFileList, FileList, fileList);
    LOCK_GETTER(const GitBranchList, BranchList, branchList);

  public slots:
    void commit(const QString &message, const QStringList &files, bool amend = false);
    void getIndex();
    void getBranches();
    void setBranch(QString branch);
    void renameCurrentBranch(QString newName);
    void createNewBranch(QString name);
    void interactiveRebase(CommitID commit, tRebaseCallback cb);
    void getLog();
    void getGraphLog();

  signals:
    void onBranchesUpdated();
    void onStatusUpdated();
    void onGraphLogUpdated();
    void onLogUpdated();


  protected:
    LOCK_GETTER(GitLog, EditableLogView, log);
    LOCK_GETTER(GitLog, EditableGraphLogView, log);
    void readRebaseList(RebaseList &list);
    void writeRebaseList(RebaseList &list);
    void parseStatus();
    QString currentBranch;
    LockableObject<GitLog> graphLog;
    LockableObject<GitLog> log;
    LockableObject<GitFileList> fileList;
    LockableObject<GitBranchList> branchList;
    QMutex logMtx;
  };
}


#undef LOCK_GETTER
#endif // GIT_HPP
