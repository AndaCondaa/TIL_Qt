#include "widget.h"
#include <QApplication>
#include <QPushButton>
#include <QLabel>

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    QPushButton *newquit = new QPushButton("종료", 0);
    this->resize(200,200);

    //quit->resize(100,50);
    //quit->move(50,150);
    newquit->setGeometry(50,150,100,50);

    connect(newquit, SIGNAL(clicked()), qApp, SLOT(quit()));
}

Widget::~Widget()
{
}
