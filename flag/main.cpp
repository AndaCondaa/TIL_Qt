#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QLabel *hello = new QLabel("Hello Qt!", 0 ,
        Qt::FramelessWindowHint | Qt::WindowSystemMenuHint| Qt::WindowStaysOnTopHint);
    hello->setCursor(Qt::ForbiddenCursor);
    hello->showMaximized();
    return a.exec();
}
