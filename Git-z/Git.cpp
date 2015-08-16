#include "Git.hpp"

#include <QDebug>
#include "A.hpp"
#include "common.hpp"
using namespace gitz;
void Git::getIndex() {
  qDebug() << "get status volano";

  A a;
  a << "status";
  a << "-s";
  addTask(a, [this]() { this->parseStatus(); });
}

void Git::getBranches() {
  A a;
  a << "branch";
  addTask(a, [this]() {
    GitBranchList list;
    while (!isOutputEnd()) {
      QString line{readOutputLine()};
      QString branchName{line.mid(2)};
      if (line.at(0) == '*') {
        list.setSelected(list.size());
        currentBranch = branchName;
      }

      list.append(branchName);
      qDebug() << list.at(list.size() - 1).getName();
      qDebug() << list.getSelected();
    }
    qDebug() << "emitim branche";
    onBranchesUpdated(list);
  });
}

void Git::setBranch(QString branch) {
  qDebug() << "set branch";
  if (branch == currentBranch) {
    qDebug() << "ignore checkout";
    return;
  }
  A a;
  a << "checkout";
  a << branch;
  addTask(a, [this]() { getBranches(); });
}

void Git::renameCurrentBranch(QString newName) {
  A a;
  a << "branch";
  a << "-m";
  a << newName;
  addTask(a, [this]() { getBranches(); });
}

void Git::createNewBranch(QString name) {
  A a;
  a << "checkout";
  a << "-b";
  a << name;
  addTask(a, [this]() { getBranches(); });
}

void Git::interactiveRebase(CommitID commit, tRebaseCallback cb) {
  A a;
  a << "rebase";
  a << "-i";
  a << commit;
  addTask(a, false, [this, cb]() {
    qDebug() << "rebasing";
    RebaseList list;
    readRebaseList(list);
    qDebug() << "zavolan read rebase list";
    cb(*this, list);
    qDebug() << "zavolan cb";
    writeRebaseList(list);
    closeWriteChannel();
    qDebug() << "zapsan rebase list";


    qDebug() << "konec";
    qDebug() << readErrorOutput();
    qDebug() << readStandardOutput();
    waitForFinished();
    qDebug() << "finisged";
  });

}

void Git::getGraph(){
    static const QString SEP="@@@";
    A a;
    a<< "log";
    a << "--graph";
    a << ("--pretty=format:"+SEP+"%ai"+SEP+"%H"+"%aN"+SEP+"%s");
    addTask(a, [this](){
        qDebug() << readStandardOutput();
    });
}

void Git::readRebaseList(RebaseList &list) {
    bool end = false;

    while (!end) {
        QString line{blockingReadOutputLine()};
    qDebug() << "lajna" << line;
    if (line.startsWith(FILE_CHAR)) {
      if (line.midRef(1).startsWith("pick"))
        list.append(line.mid(6, 7));

    } else if (line.startsWith(END_FILE_CHAR)) {
      qDebug() << "konec";
      end = true;
    }
  }
}

void Git::writeRebaseList(RebaseList &list){
    for (const RebaseList::rebaseItem* item:list){
        qDebug() << item->op << ' ' << item->commit << '\n';
        writeToProcess(item->op);
        writeToProcess(' ');
        writeToProcess(item->commit);
        writeToProcess('\n');
    }
    writeToProcess(END_OF_INPUT);
    writeToProcess('\n');
}

void Git::parseStatus() {
    GitFileList list;
    while (!isOutputEnd()) {
        QString line{readOutputLine()};
        qDebug() << line;
        GitFile::state fileState;

        if (line.startsWith("??")) {
            fileState = GitFile::state::CREATED;
        } else if (line.startsWith(" M")) {
            fileState = GitFile::state::MODIFIED;
    } else if (line.startsWith(" D")) {
      fileState = GitFile::state::REMOVED;
    } else {
      fileState = GitFile::state::UNKNOWN;
    }
    QString filename = line.mid(3);

    list.append(GitFile{filename, fileState});
  }
  qDebug() << "emitim status\n";
  onStatusUpdated(list);
}

void Git::commit(const QString &message, const QStringList &files, bool amend) {
  if (files.empty()) {
    qDebug() << "commit ignored";
    return;
  }
  A a;

  a << "add";
  a << files;

  addTask(a, [this, message, amend]() {

    A a;
    a << "commit";
    if (amend) {
      if (!message.isEmpty()) {
        a << "--message" << message;
      }
      a << "--amend";
    } else {
      a << "--message" << message;
    }

    runExec(a);
    waitForFinished();
    getIndex();
  });
}
