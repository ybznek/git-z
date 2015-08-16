#ifndef GRAPHVIEWWIDGET_HPP
#define GRAPHVIEWWIDGET_HPP
#include <QWidget>
#include <QPainter>
#include <GitLog.hpp>
#include <QPaintEvent>
#include <QBrush>
#include <QColor>
using namespace gitz;
class GraphViewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GraphViewWidget(QWidget *parent = nullptr):QWidget{parent}{
    }
    inline void setLog(const GitLog& log){this->log=&log;}
    void paintEvent(QPaintEvent* event) override
    {
        qDebug() << "top" << event->region().boundingRect().top();;
        QPainter p{this};
        p.setBackground(backgroundBrush);
        p.fillRect(this->geometry(),backgroundBrush);
        int w=this->geometry().width();
        int h=this->geometry().height();
        p.setPen(Qt::green);
        p.drawLine(0,0,w,h);
        int i=0;
        qDebug() << "len" << log->length();
        for(const GitLogItem& it : *log){
                p.drawText(20,20*i, it.getCommitHash());
                p.drawText(20,20*i, it.getCommitHash());
                qDebug() << it.getCommitHash();
                ++i;
        }

    }
signals:

public slots:
protected:
        const GitLog* log=nullptr;
        const QBrush backgroundBrush{QColor{255,255,255}};
};

#endif // GRAPHVIEWWIDGET_HPP
