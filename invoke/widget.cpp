#include "widget.h"
#include <QObject>
#include <QEvent>
#include <QKeyEvent>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
}

Widget::~Widget()
{
}


bool Widget::event(QEvent* e)
{
    if(e->type() == QEvent::KeyPress){

        QKeyEvent* ke = (QKeyEvent*)e;
        qDebug() << ke->text();
        if(ke->key() == Qt::Key_Tab){
            ke->accept();
            return true;
        }
    } else if (e->type() >= QEvent::User){
        //QCustomEvent* c = (QCustomEvent*)e;
        qDebug()<<"User " << e->type();
        return true;
    }
    return false;
}
