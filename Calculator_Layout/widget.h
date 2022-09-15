#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QLabel;
class QButtonGroup;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QLabel* label;
    QString num, op;
    QButtonGroup* buttonGroup;

public slots:
    void numButton();
    void opButton();
};
#endif // WIDGET_H
