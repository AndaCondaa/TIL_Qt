//#include "lcdnumber.h"

#include <QApplication>
#include <QLCDNumber>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget* widget = new QWidget(0);

    QLCDNumber *lcd1 = new QLCDNumber(widget);
    lcd1->setSegmentStyle(QLCDNumber::Flat);
    lcd1->setDecMode();
    lcd1->display(1111);
    lcd1->move(10,10);

    QLCDNumber *lcd2 = new QLCDNumber(widget);
    lcd2->setSegmentStyle(QLCDNumber::Flat);
    lcd2->display(16);
    lcd2->setBinMode();
//    QObject::connect(lcd2, &QLCDNumber::overflow,
//                     lcd2, [](){qDebug("Overflow");});
    lcd2->move(10,40);

    widget->resize(120,80);
    widget->show();


//    LCDNumber w;
//    w.show();

    return a.exec();
}
