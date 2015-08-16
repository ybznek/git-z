#ifndef GIT_HPP
#define GIT_HPP
#include "GitProcess.hpp"
#include <QObject>
#include "GitFileList.hpp"
#include "GitBranchList.hpp"
#include "CommitID.hpp"
#include "RebaseList.hpp"
#include "GitLog.hpp"
namespace gitz {
  class Git : public GitProcess {
    Q_OBJECT

  public:
    Git(const QString &executable) { insertProcessEnvironment("GIT_SEQUENCE_EDITOR", executable + " edit"); }
    ~Git() {}
    using tRebaseCallback = std::function<void(Git &, RebaseList &)>;

  signals:
    void onBranchesUpdated(const GitBranchList &branchList);
    void onStatusUpdated(const GitFileList &list);

  public slots:
    void commit(const QString &message, const QStringList &files, bool amend = false);
    void getIndex();
    void getBranches();
    void setBranch(QString branch);
    void renameCurrentBranch(QString newName);
    void createNewBranch(QString name);
    void interactiveRebase(CommitID commit, tRebaseCallback cb);
    void getGraph();

  protected:
    void readRebaseList(RebaseList &list);
    void writeRebaseList(RebaseList &list);
    void parseStatus();
    QString currentBranch;
    GitLog graph;
  };
}
#endif // GIT_HPP
