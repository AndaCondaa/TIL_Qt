#include "widget.h"
#include <QApplication>
#include <QPushButton>
#include <QLabel>

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    QPushButton *quit = new QPushButton("종료", this);
    this->resize(200,200);

    //quit->resize(100,50);
    //quit->move(50,150);
    quit->setGeometry(50,150,100,50);

    connect(quit, SIGNAL(clicked()), this, SLOT(slotQuit()));
    //connect(quit, &QPushButton::clicked, qApp, &QApplication::quit);
    //connect(quit, &QPushButton::clicked, [](){qApp->quit();});

    QLabel *label = new QLabel("<font size=150 color=red>종료버튼!</font>", this);
    label->setGeometry(50,50,200,50);
    label->setObjectName("label1");
}

Widget::~Widget()
{
}

void Widget::slotQuit()
{
    QLabel *label = findChild<QLabel*>("label1");
    qDebug("%s", qPrintable(label->metaObject()->className()));
    label->setText("World");
}

void Widget::processClick()
{
    emit widgetClicked();
}
