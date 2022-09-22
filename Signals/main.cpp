#include "counter.h"
#include <QCoreApplication>
#include <QDebug>
#include <QVariant>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    Counter a, b;
    Counter::connect(&a, SIGNAL(valueChanged(int)), &b, SLOT(setValue(int)));
    a.setValue(30);
    qDebug("%d", b.value());
    b.setObjectName("bar");
    qDebug() << b.property("objectName");

    return app.exec();
}
