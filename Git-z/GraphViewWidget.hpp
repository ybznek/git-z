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
        qDebug() << "len" << log->length();
        int length=log->length();
        int pos=0;
        p.setFont(QFont("arial",20-2));
        for (int i=scroll;i<length;++i){
            ++pos;
               const GitLogItem& it = (*log)[i];
                p.drawText(20,20*pos, it.getCommitHash());
                qDebug() << it.getCommitHash();
                ++i;
        }
}

signals:

public slots:
    void onScroll(int scroll) {
        this->scroll = scroll;
        repaint();
    }
protected:
        int scroll = 0;
        const GitLog* log = nullptr;
        const QBrush backgroundBrush{QColor{255,255,255}};
};

#endif // GRAPHVIEWWIDGET_HPP
