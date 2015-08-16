#include "LogView.hpp"
#include "ui_LogView.h"

LogView::LogView(Git& git, QWidget *parent) : QDialog{parent}, git{git}, ui{new Ui::LogView} {
  ui->setupUi(this);
  ui->widget->setLog(git.getLogView());
  QObject::connect(&git, SIGNAL(onLogUpdated()), this, SLOT(updateLog()));

  QObject::connect(ui->pushButton, SIGNAL(clicked(bool)), &git, SLOT(getLog()));

}

LogView::~LogView() { delete ui; }

void LogView::updateLog(){
    ui->widget->repaint();
    qDebug() << "should repaint";
}
