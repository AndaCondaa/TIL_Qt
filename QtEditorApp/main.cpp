#include "qteditor.h"

#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    translator.load("_ko");
    a.installTranslator(&translator);

    QtEditor w;
    w.show();
    return a.exec();
}
