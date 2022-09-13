#ifndef CALCULATORWIDGET_H
#define CALCULATORWIDGET_H

#include <QWidget>

class QLabel;

class CalculatorWidget : public QWidget
{
    Q_OBJECT

public:
    CalculatorWidget(QWidget *parent = nullptr);
    ~CalculatorWidget();

private:
    QLabel* label;
    QString num, op;

public slots:
    /*
    void num0();
    void num1();
    void num2();
    void num3();
    void num4();
    void num5();
    void num6();
    void num7();
    void num8();
    void num9();

    void plus();
    void min();
    void mul();
    void div();
    */

    void numButton();
    void opButton();
};
#endif // CALCULATORWIDGET_H
