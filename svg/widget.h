#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QImage buffer;

public:
    void paintEvent(QPaintEvent*);
};
#endif // WIDGET_H
