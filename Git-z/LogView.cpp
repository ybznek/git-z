#include "LogView.hpp"
#include "ui_LogView.h"

LogView::LogView(Git& git, QWidget *parent) : QDialog(parent), git{git}, ui(new Ui::LogView) {
  ui->setupUi(this);

  QObject::connect(&git, SIGNAL(onLogUpdated(const GitLog*)), this, SLOT(updateGraph(const GitLog*)));

}

LogView::~LogView() { delete ui; }
