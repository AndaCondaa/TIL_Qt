#include <QApplication>
#include <QProgressBar>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QProgressBar *pb = new QProgressBar();
    pb->setRange(0,60);
    pb->setValue(20);
    pb->setInvertedAppearance(true);
    pb->setTextVisible(true);
    pb->show();

    QTimer timer;
    int n = 0;
    QObject::connect(&timer, &QTimer::timeout,
                     [&]{pb->setValue(++n%101);});

    timer.start(1000);        //ms주기로 QTimer 객체를 연속 실행

    return a.exec();
}
