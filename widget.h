#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QTimer>
#include <QLabel>
#include <QHBoxLayout>

class Widget : public QWidget
{
    Q_OBJECT

    QList <QPoint> g_mouse_list;
    QLabel* testLabel;
    bool mouse_pressed;
    int g_rad;

protected:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent* pe);
    void mouseMoveEvent(QMouseEvent* pe);

public:
    Widget(QWidget *parent = 0);

private slots:
    void timeTick();
};

#endif // WIDGET_H
