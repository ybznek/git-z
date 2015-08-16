#ifndef LOGVIEW_HPP
#define LOGVIEW_HPP

#include <QDialog>
#include "Git.hpp"
#include "GitLog.hpp"

using namespace gitz;

namespace Ui {
  class LogView;
}

class LogView : public QDialog {
  Q_OBJECT

public:
  explicit LogView(Git& git, QWidget *parent = 0);
  ~LogView();

protected slots:
  void updateGraph(const GitLog *log) {
      qDebug() << "mam novy graf";
    for (const GitLogItem &item : *log) {
      qDebug() << item.getCommitId();
    }
  }
public:
  void updateLog(){
      git.getLog();
  }

private:
  Git& git;
  Ui::LogView *ui;
};

#endif // LOGVIEW_HPP
