#include "object.h"
#include <QCoreApplication>
#include <QDebug>
#include <QScopedPointer>

void Do(QScopedPointer<Object> &mypointer)
{
    qInfo()<< ">>>>Do" << mypointer.data();
}

void use(Object* obj)
{
    if(!obj) return;
    qInfo() << ">>> Use" << obj;
}

void doStuff()
{
    //Object* obj = new Object(); //dangling pointer!!
    QScopedPointer<Object> mypointer(new Object());

    use(mypointer.data());
    Do(mypointer);
}   //pointer is automatically deleted!!


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QObject* obj1 = new Object(nullptr);
    obj1->setObjectName("MyObject");
    QPointer<QObject>p(obj1);
    Object obj2;
    obj2.widget = p;
    obj2.useWidget();
    //delete obj1;
    obj2.useWidget();

    for(int i = 0; i < 10; i++)
    {
        qInfo() << "----------" << i;
        doStuff();
    }

    doStuff();

    return a.exec();
}
