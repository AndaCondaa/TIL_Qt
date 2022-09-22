#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>

class Widget : public QLabel
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void moveEvent(QMoveEvent*);
    void closeEvent(QCloseEvent*);
};
#endif // WIDGET_H
