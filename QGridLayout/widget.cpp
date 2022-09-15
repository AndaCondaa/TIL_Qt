#include "widget.h"
#include <QGridLayout>
#include <QPushButton>
#define ROW 3

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QGridLayout* gridLayout = new QGridLayout;
    QPushButton* pushButton[ROW * ROW];
    for(int y = 0; y < ROW; y++){
        for(int x = 0; x < ROW; x++){
            int p = x+y*ROW;
            QString str = QString("Button%1").arg(p+1);
            pushButton[p] = new QPushButton(str, this);
            gridLayout->addWidget(pushButton[p], y, x);
        }
    }
    setLayout(gridLayout);
}

Widget::~Widget()
{
}

