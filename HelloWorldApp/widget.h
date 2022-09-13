#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

signals:
    void widgetClicked();

public slots:
    void slotQuit();
    void processClick();

};
#endif // WIDGET_H
