#include "worker.h"

Worker::Worker(QObject *parent, QStringList* data, QSemaphore* sema, int position)
    : QObject{parent}
{
    this->sema = sema;
    this->data = data;
    this->position = position;
}

void Worker::run()
{
    if(!data || !sema){
        qInfo() << "Missing pointers!";
        return;
    }

    QString t = QString( "0x%1" ).arg((long)QThread::currentThreadId(), 16);
    sema->acquire(1);
    data->replace(position, QString::number(position) + "-" + t);
    sema->release();
    qInfo() << t << "Finished" << position;
}
