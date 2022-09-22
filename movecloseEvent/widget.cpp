#include "widget.h"
#include <QCloseEvent>
#include <QLabel>
#include <QString>

Widget::Widget(QWidget *parent)
    : QLabel(parent)
{
    setText(tr("Hello World"));
    resize(100,30);
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
    event->ignore();        //accept();
}
