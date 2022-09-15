#include "widget.h"
#include <QFrame>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QFrame* line1 = new QFrame(this);
    line1->setGeometry(QRect(0,0,270,16));
    line1->setLineWidth(2);
    line1->setFrameStyle(QFrame::HLine | QFrame::Plain);

    QFrame* line2 = new QFrame(this);
    line2->setGeometry(QRect(0,20,270,16));
    line2->setLineWidth(2);
    line2->setFrameStyle(QFrame::HLine | QFrame::Raised);

    QFrame* line3 = new QFrame(this);
    line3->setGeometry(QRect(0,40,270,16));
    line3->setLineWidth(2);
    line3->setFrameStyle(QFrame::HLine | QFrame::Sunken);

}

Widget::~Widget()
{
}

