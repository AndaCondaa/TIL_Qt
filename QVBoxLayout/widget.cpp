#include "widget.h"
#include <QVBoxLayout>
#include <QPushButton>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QPushButton* pushButton1 = new QPushButton();
    pushButton1->setText("Butto1");
    QPushButton* pushButton2 = new QPushButton("Button2");
    QPushButton* pushButton3 = new QPushButton("Button3",this);

    QVBoxLayout* vBoxLayout = new QVBoxLayout(this);
    vBoxLayout->setContentsMargins(10, 10 , 10, 10);
    vBoxLayout->setSpacing(30);
    vBoxLayout->addWidget(pushButton1);
    vBoxLayout->addWidget(pushButton2);
    vBoxLayout->addWidget(pushButton3);
    //setLayout(vBoxLayout);
}

Widget::~Widget()
{
}
