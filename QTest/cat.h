#ifndef CAT_H
#define CAT_H

#include <QWidget>

class Cat : public QObject
{
    Q_OBJECT

public:
    explicit Cat(QObject *parent = nullptr);
    void test();

private slots:
    void meow();
    void sleep();
    void speak(QString value);
};
#endif // CAT_H
