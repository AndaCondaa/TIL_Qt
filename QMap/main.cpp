#include <QCoreApplication>
#include <QMap>
#include <QHash>
#include <QDebug>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QMap<QString, int> ages;
    //QHash<QString, int> ages;
    ages.insert("Bryan", 44);
    ages.insert("Tammy", 49);
    ages.insert("Heather", 25);
    ages.insert("Chris", 27);
    ages.insert("Rango", 15);

    qInfo() << "Bryan is " <<ages["Bryan"] << "years old";
    qInfo() << "Keys:" << ages.keys();
    qInfo() << "Size:" << ages.size();

    foreach(QString key, ages.keys())
        qInfo() << key << "=" << ages[key];

    return a.exec();
}
