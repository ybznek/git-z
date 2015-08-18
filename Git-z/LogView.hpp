#ifndef LOGVIEW_HPP
#define LOGVIEW_HPP

#include <QDialog>
#include "Git.hpp"
#include "GitLog.hpp"
#include "GraphViewWidget.hpp"
using namespace gitz;
using namespace gitz::widget;

namespace Ui {
  class LogView;
}

class LogView : public QDialog {
  Q_OBJECT

public:
  explicit LogView(Git &git, QWidget *parent = nullptr);
  ~LogView();

public slots:
  void updateLog();

private:
  Git &git;
  Ui::LogView *ui;
};

#endif // LOGVIEW_HPP
