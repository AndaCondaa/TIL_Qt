#include "widget.h"
#include <QCheckBox>
#include <QButtonGroup>
#include <QLabel>
#include <QString>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    label = new QLabel("NONE", this);
    label->setGeometry(10,10,50,10);

    resize(140,110);
    buttonGroup = new QButtonGroup(this);
    buttonGroup->setExclusive(false);
    connect(buttonGroup, SIGNAL(idClicked(int)), SLOT(selectButton(int)));
    for(int i =0; i<4; i++){
        QString str = QString("RadioButton%1").arg(i+1);  //%1 첫 번째 arg값을 받게됨.
        checkBox[i] = new QCheckBox(str, this);
        checkBox[i]->move(10, 20+20*i);
        buttonGroup->addButton(checkBox[i], i);
    }
}

Widget::~Widget()
{
}

void Widget::selectButton(int id)
{
    QButtonGroup* buttonGroup = (QButtonGroup*)sender();
    QCheckBox* button = (QCheckBox*)buttonGroup->button(id);

    QString str = QString::number(id+1);
    label->setText(str);

    qDebug("CheckBox%d is selected(%s)",id+1,
                        (button->isChecked())?"on":"off");
}


