#include "LogView.hpp"
#include "ui_LogView.h"

LogView::LogView(Git &git, QWidget *parent) : QDialog{parent}, git{git}, ui{new Ui::LogView} {
  ui->setupUi(this);
  ui->widget->setGit(&git);
  QObject::connect(&git, SIGNAL(onLogUpdated()), this, SLOT(updateLog()));

  QObject::connect(ui->pushButton, SIGNAL(clicked(bool)), &git, SLOT(getLog()));

  QObject::connect(ui->verticalScrollBar, SIGNAL(sliderMoved(int)), ui->widget, SLOT(onScroll(int)));
}

LogView::~LogView() { delete ui; }

void LogView::updateLog() {
  emit ui->widget->notifyDataChanged();
  //    ui->widget->repaint();
  qDebug() << "should repaint";
}
