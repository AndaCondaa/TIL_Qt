#include "widget.h"
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QButtonGroup>

#define WIDTH 4

Widget::Widget(QWidget *parent) : QWidget(parent)
{
//GUI 구성
    char str[16][2] = {
        "7", "8", "9", "/",
        "4", "5", "6", "x",
        "1", "2", "3", "-",
        "0", "C", "=", "+"
    };

    label = new QLabel("0", this);
    label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    label->setObjectName("label1");
    label->setFrameStyle(QFrame::StyledPanel);



    QGridLayout* gridButton = new QGridLayout;
    QPushButton* button[16];
    for(int y=0; y<WIDTH; y++)
    {
        for(int x=0; x<WIDTH; x++)
        {
            button[x+y*WIDTH] = new QPushButton(str[x+y*WIDTH]);
            gridButton->addWidget(button[x+y*WIDTH], y, x);
        }
    }
    gridButton->setSpacing(20);



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

    QVBoxLayout* vBox = new QVBoxLayout(this);
    vBox->setSpacing(10);
    vBox->addWidget(label);
    vBox->addLayout(gridButton);
    setLayout(vBox);
}

Widget::~Widget()
{
}


void Widget::numButton()
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

void Widget::opButton()
{
    QPushButton* button = dynamic_cast<QPushButton*>(sender());
    if(button != nullptr) op = button->text();
    QLabel* label = findChild<QLabel*>("label1");
    if(label != nullptr) {
        num = label->text();
        label->setText("0");
    }
}

