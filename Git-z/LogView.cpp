#include "LogView.hpp"
#include "ui_LogView.h"

LogView::LogView(Git* git,QWidget *parent) :
    QDialog(parent),
    git{git},
    ui(new Ui::LogView)
{
    ui->setupUi(this);
}

LogView::~LogView()
{
    delete ui;
}
