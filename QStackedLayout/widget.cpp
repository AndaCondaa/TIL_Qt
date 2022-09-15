#include "widget.h"
#include <QstackedLayout>
#include <QHBoxLayout>
#include <QDial>
#include <QLabel>
#include <QCalendarWidget>
#include <QTextEdit>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QDial* dial = new QDial(this);
    dial->setRange(0, 2);

    QLabel* label = new QLabel("Stack1 ", this);
    QCalendarWidget* calendarWidget = new QCalendarWidget(this);
    QTextEdit* textEdit = new QTextEdit("Stack 3", this);

    QStackedLayout* stackedLayout = new QStackedLayout(this);
    stackedLayout->addWidget(label);
    stackedLayout->addWidget(calendarWidget);
    stackedLayout->addWidget(textEdit);


    connect(dial, SIGNAL(valueChanged(int)),\
            stackedLayout, SLOT(setCurrentIndex(int)));

    QHBoxLayout* hBoxLayout = new QHBoxLayout();
    hBoxLayout->addWidget(dial);
    hBoxLayout->addLayout(stackedLayout);

    setLayout(hBoxLayout);
}

Widget::~Widget()
{
}

