#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QEvent;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    bool event(QEvent* e);
};
#endif // WIDGET_H
