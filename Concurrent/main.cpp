#include <QApplication>
#include <QtConcurrent>
#include <QApplication>
#include <QProgressDialog>

using namespace QtConcurrent;
const int iterations = 500;

static void spin(int &iteration)
{
    const int work = 1000 * 1000 * 40;
    volatile int v = 0;
    for(int j = 0; j < work; ++j) ++v;
    qDebug() << "iteration" << iteration << "int thread" << QThread::currentThread();
}

static void display(const QString &msg)
{
    qDebug() << __func__ << QThread::currentThread() << msg;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << "Main thread" << QThread::currentThreadId();

    QVector<int> vector;
    for (int i = 0; i < iterations; ++i) vector.append(i);

    QProgressDialog dialog;
    dialog.setLabelText(QString("thread %1").arg(QThread::idealThreadCount()));

    QFutureWatcher<void> futureWatcher;
    QObject::connect(&futureWatcher, SIGNAL(finished()),
                     &dialog, SLOT(reset()));
    QObject::connect(&futureWatcher, SIGNAL(progressRangeChanged(int, int)),
                     &dialog, SLOT(setRange(int, int)));
    QObject::connect(&futureWatcher, SIGNAL(progressValueChanged(int)),
                     &dialog, SLOT(setValue(int)));
    QObject::connect(&dialog, SIGNAL(canceled()),
                     &futureWatcher, SLOT(cancel()));

    futureWatcher.setFuture(QtConcurrent::map(vector,spin));

    dialog.exec();

    QFuture<void> future = QtConcurrent::run(display, QObject::tr("Hello, world"));
    futureWatcher.setFuture(future);

    futureWatcher.waitForFinished();

    qDebug() << "Canceled?" << futureWatcher.future().isCanceled();

    return a.exec();
}
