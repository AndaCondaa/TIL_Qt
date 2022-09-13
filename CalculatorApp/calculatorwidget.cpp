#include "calculatorwidget.h"
#include <QLabel>
#include <QPushButton>
#define WIDTH 4

CalculatorWidget::CalculatorWidget(QWidget *parent) : QWidget(parent)
{
//GUI 구성
    char str[16][2] = {
        "7", "8", "9", "/",
        "4", "5", "6", "x",
        "1", "2", "3", "-",
        "0", "C", "=", "+"
    };

    label = new QLabel("0", this);
    label->setGeometry(5, 5, 390, 90);
    label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    label->setObjectName("label1");
    label->setFrameStyle(QFrame::Box);

    QPushButton* button[16];
    for(int y=0; y<WIDTH; y++)
    {
        for(int x=0; x<WIDTH; x++)
        {
            button[x+y*WIDTH] = new QPushButton(str[x+y*WIDTH], this);
            button[x+y*WIDTH]->setGeometry(100*x, 100+100*y, 100, 100);
        }
    }

//버튼->번호
    connect(button[12],SIGNAL(clicked()), SLOT(numButton()));
    connect(button[8],SIGNAL(clicked()), SLOT(numButton()));
    connect(button[9],SIGNAL(clicked()), SLOT(numButton()));
    connect(button[10],SIGNAL(clicked()), SLOT(numButton()));
    connect(button[4],SIGNAL(clicked()), SLOT(numButton()));
    connect(button[5],SIGNAL(clicked()), SLOT(numButton()));
    connect(button[6],SIGNAL(clicked()), SLOT(numButton()));
    connect(button[0],SIGNAL(clicked()), SLOT(numButton()));
    connect(button[1],SIGNAL(clicked()), SLOT(numButton()));
    connect(button[2],SIGNAL(clicked()), SLOT(numButton()));
//버튼->연산자
    connect(button[13], &QPushButton::clicked, [=](){ label->setText("0"); });
    connect(button[15],SIGNAL(clicked()), SLOT(opButton()));
    connect(button[11],SIGNAL(clicked()), SLOT(opButton()));
    connect(button[7],SIGNAL(clicked()), SLOT(opButton()));
    connect(button[3],SIGNAL(clicked()), SLOT(opButton()));
    connect(button[14], &QPushButton::clicked,
            [=](){
        double result = 0;
        if(op == "+"){
            result = num.toDouble() + label->text().toDouble();
        } else if(op == "-"){
            result = num.toDouble() - label->text().toDouble();
        } else if(op == "x"){
            result = num.toDouble() * label->text().toDouble();
        } else if(op == "/"){
            result = num.toDouble() / label->text().toDouble();
        }
        label->setText(QString::number(result));
    });

}

CalculatorWidget::~CalculatorWidget()
{
}

/*
void CalculatorWidget::plus()
{
    op = "+";
    num = label->text();
    label->setText("0");
}
void CalculatorWidget::min()
{
    op = "-";
    num = label->text();
    label->setText("0");
}
void CalculatorWidget::mul()
{
    op = "x";
    num = label->text();
    label->setText("0");
}
void CalculatorWidget::div()
{
    op = "/";
    num = label->text();
    label->setText("0");
}


void CalculatorWidget::num0()
{
    QString str = label->text();
    label->setText(str=="0"?"0":str+"0");
}
void CalculatorWidget::num1()
{
    QString str = label->text();
    label->setText(str=="0"?"1":str+"1");
}
void CalculatorWidget::num2()
{
    QString str = label->text();
    label->setText(str=="0"?"2":str+"2");
}
void CalculatorWidget::num3()
{
    QString str = label->text();
    label->setText(str=="0"?"3":str+"3");
}
void CalculatorWidget::num4()
{
    QString str = label->text();
    label->setText(str=="0"?"4":str+"4");
}
void CalculatorWidget::num5()
{
    QString str = label->text();
    label->setText(str=="0"?"5":str+"5");
}
void CalculatorWidget::num6()
{
    QString str = label->text();
    label->setText(str=="0"?"6":str+"6");
}
void CalculatorWidget::num7()
{
    QString str = label->text();
    label->setText(str=="0"?"7":str+"7");
}
void CalculatorWidget::num8()
{
    QString str = label->text();
    label->setText(str=="0"?"8":str+"8");
}
void CalculatorWidget::num9()
{
    QString str = label->text();
    label->setText(str=="0"?"9":str+"9");
}
*/

void CalculatorWidget::numButton()
{
    QPushButton* button = dynamic_cast<QPushButton*>(sender());
    QString bStr;
    if(button != nullptr) bStr = button->text();
    QLabel* label = findChild<QLabel*>("label1");
    if(label != nullptr) {
        QString lStr = label->text();
        label->setText(label->text()=="0"?bStr:lStr+bStr);
    }
}

void CalculatorWidget::opButton()
{
    QPushButton* button = dynamic_cast<QPushButton*>(sender());
    if(button != nullptr) op = button->text();
    QLabel* label = findChild<QLabel*>("label1");
    if(label != nullptr) {
        num = label->text();
        label->setText("0");
    }
}

