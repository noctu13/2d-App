#include "widget.h"

Widget::Widget(QWidget *parent): QWidget(parent){
    this->setMinimumSize(QSize(800,600));
    QTimer* mainTimer = new QTimer(this);
    connect(mainTimer,SIGNAL(timeout()),this,SLOT(timeTick()));
    mainTimer->start(10);
    QHBoxLayout* hLayout = new QHBoxLayout(this);
    testLabel = new QLabel("Message");
    hLayout->addWidget(testLabel);
    g_rad = 30;
    mouse_pressed = false;
}

void Widget::paintEvent(QPaintEvent* e){
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 1));
    for(QList<QPoint>::const_iterator i=g_mouse_list.begin(); i!=g_mouse_list.end(); ++i)
        painter.drawEllipse(*i,g_rad,g_rad);
    QWidget::paintEvent(e);
}

void Widget::mousePressEvent(QMouseEvent* pe){
    g_mouse_list.push_back(QPoint(pe->x(),pe->y()));
}

void Widget::mouseMoveEvent(QMouseEvent* pe){
    g_mouse_list.back()=pe->pos();
    update();
}

void Widget::timeTick(void){
    for(QList<QPoint>::iterator i=g_mouse_list.begin(); i!=g_mouse_list.end();++i){
        for(QList<QPoint>::iterator j=g_mouse_list.begin(); j!=g_mouse_list.end();++j){
            if(i==j) continue;
            int x=(*i).x()-(*j).x(),
                y=(*i).y()-(*j).y();
            if(sqrt(x*x+y*y)<2*g_rad){
                int t=1;
                if(x==0){
                    if(y<0)t=-1;
                    (*i).ry()=2*t*g_rad+(*j).y();
                }else{
                    double alpha=atan(y/(1.0*x));
                    if(x<0)t=-1;
                    (*i).rx()=2*t*g_rad*cos(alpha)+(*j).x();
                    (*i).ry()=2*t*g_rad*sin(alpha)+(*j).y();
                }
            }
            //if((*i).x()<0) //(*j).y()>this->minimumHeight()
                //j=g_mouse_list.erase(j);
            //else

        }
    }
    QString::number(g_mouse_list.size());
    update();
}
