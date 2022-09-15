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

    QButtonGroup* buttonGroup = new QButtonGroup(this);
    connect(buttonGroup, SIGNAL(idClicked(int)), SLOT(click(int)));
    QGridLayout* gridButton = new QGridLayout;
    QPushButton* button[16];
    for(int y=0; y<WIDTH; y++)
    {
        for(int x=0; x<WIDTH; x++)
        {
            button[x+y*WIDTH] = new QPushButton(str[x+y*WIDTH]);
            gridButton->addWidget(button[x+y*WIDTH], y, x);
            buttonGroup->addButton(button[x+y*WIDTH],x+y*WIDTH);
        }
    }
    gridButton->setSpacing(20);


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

void Widget::click(int id)
{
    double result = 0;
    QPushButton* clickButton = (QPushButton*)((QButtonGroup*)sender())->button(id);
    QString str = clickButton->text();
    switch(id){
    case 0: case 1: case 2: case 4: case 5: case 6: case 8: case 9: case 10: case 12:
        label->setText((label->text()=="0")?(str):(str+label->text()));
        break;
    case 3: case 7: case 11: case 15:
        num = label->text();
        op = clickButton->text();
        label->setText("0");
        break;
    case 13:
        label->setText("0");
        break;
    case 14:
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
        break;
    }
}
