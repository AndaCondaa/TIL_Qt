
#include "domreader.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DOMReader d;
    d.show();
    return a.exec();
}
