#ifndef LOGVIEW_HPP
#define LOGVIEW_HPP

#include <QDialog>
#include "Git.hpp"
using namespace gitz;
namespace Ui {
class LogView;
}

class LogView : public QDialog
{
    Q_OBJECT

public:
    explicit LogView(Git* git,QWidget *parent = 0);
    ~LogView();

private:
    Git* git;
    Ui::LogView *ui;
};

#endif // LOGVIEW_HPP
