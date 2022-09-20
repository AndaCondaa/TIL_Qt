#ifndef OBJECT_H
#define OBJECT_H

#include <QObject>
#include <QPointer>

class Object : public QObject
{
public:
    explicit Object(QObject *parent = nullptr);
    ~Object();
    void useWidget();

    QPointer<QObject> widget;

signals:

};

#endif // OBJECT_H
