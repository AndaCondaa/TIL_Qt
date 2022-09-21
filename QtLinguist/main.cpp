#include <QApplication>
#include <QtWidgets>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    translator.load("hello_ko");
    a.installTranslator(&translator);

    QPushButton hello(QObject::tr("Hello world"));
    hello.resize(100,30);
    hello.show();

    return a.exec();
}
