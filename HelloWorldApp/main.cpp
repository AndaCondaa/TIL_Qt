#include "widget.h"
#include <QApplication>
#include <QPushButton>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Widget *widget = new Widget(0); //인자 안쓰면 nullptr -> default
    widget->show();

    return app.exec();
}
