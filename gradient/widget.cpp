#include "widget.h"
#include <QPainter>
#include <QPainterPath>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(200,200);
}

Widget::~Widget()
{
}

void Widget::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

////Gradient
//    //QLinearGradient gradient(0, 0, 100 ,180);
//    QRadialGradient gradient(102, 102, 85);
//    gradient.setColorAt(0.0,Qt::red);
//    gradient.setColorAt(0.5, Qt::yellow);
//    gradient.setColorAt(1.0, Qt::blue);

//    QPainter painter;
//    painter.begin(this);
//    painter.setBrush(gradient);
//    painter.drawRect(20,20,160,160);
//    painter.end();

//PainterPath
    QPainterPath path;
    path.addRect(20, 20, 60, 60);

    path.moveTo(0, 0);
    path.cubicTo(99, 0,  50, 50,  99, 99);
    path.cubicTo(0, 99,  50, 50,  0, 0);

    QPainter painter(this);
    painter.fillRect(0, 0, 100, 100, Qt::white);
    painter.setPen(QPen(QColor(79, 106, 25), 1, Qt::SolidLine,
                        Qt::FlatCap, Qt::MiterJoin));
    painter.setBrush(QColor(122, 163, 39));

    painter.drawPath(path);

}
