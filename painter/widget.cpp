#include "widget.h"
#include <QPainter>
#include <QFont>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(200,200);
}

Widget::~Widget()
{
}

void Widget::paintEvent(QPaintEvent*)
{
    QPainter *painter = new QPainter(this);
    //painter->setPen(QPen(Qt::blue, 10, Qt::DashLine));
    painter->setPen(QPen(Qt::blue, 5, Qt::SolidLine));
    //painter->drawPoint(100,100);
    //painter->drawLine(20, 20, 160, 160);
    //painter->drawRect(20,20,160,160);
    //painter->drawRoundedRect(20,20,160,160,100,80);
    //painter->drawEllipse(20,20,140,170);
    //painter->drawArc(20,20,160,160,30*16,150*16);
    //painter->drawChord(20,20,160,160,30*16,150*16);
    //painter->drawPie(20,20,160,160,50*16,130*16);
//    static const QPoint points[6] = {
//        QPoint(20, 20),
//        QPoint(20, 90),
//        QPoint(90, 80),
//        QPoint(80, 160),
//        QPoint(160, 80),
//        QPoint(80, 20)
//    };


    //painter->drawPolygon(points, 6);
    //painter->drawPolyline(points, 6);
    //painter->drawLines(points, 6);
    //painter->drawPoints(points, 6);

    QFont serifFont("Times", 20, 1000, true);
    serifFont.setWeight(QFont::Thin);
    painter->setFont(serifFont);
    painter->drawText(20, 50, "여왕 럭스!");

    delete painter;
}
