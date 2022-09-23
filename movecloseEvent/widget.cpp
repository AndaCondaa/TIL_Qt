#include "widget.h"
#include <QCloseEvent>
#include <QLabel>
#include <QString>

Widget::Widget(QWidget *parent)
    : QLabel(parent)
{
    setText("Timer");
    resize(100,30);

    int id1 = startTimer(3000);
    int id2 = startTimer(1000);
}

Widget::~Widget()
{
}

void Widget::moveEvent(QMoveEvent*)
{
    setText(QString("X: %1, Y: %2").arg(x()).arg(y()));
}

void Widget::closeEvent(QCloseEvent* event)
{
    event->accept();        //ignore();
}

void Widget::timerEvent(QTimerEvent* event)
{
    setText(QString::number(event->timerId()));
}
