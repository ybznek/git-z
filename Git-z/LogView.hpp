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
  explicit LogView(Git& git, QWidget *parent = nullptr);
  ~LogView();

public slots:
  void updateLog();

private:
  Git& git;
  Ui::LogView *ui;
};

#endif // LOGVIEW_HPP
