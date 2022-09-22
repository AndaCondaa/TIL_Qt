#include "widget.h"
#include "filter.h"
#include "application.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    Application a(argc, argv);
    Widget w;
    w.show();
    Filter* filter = new Filter(&w);
    a.installEventFilter(filter);

    return a.exec();
}
