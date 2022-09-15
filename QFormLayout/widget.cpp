#include "widget.h"
#include <QFormLayout>
#include <QLineEdit>
#include <QDateEdit>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QLineEdit* ipAddressLineEdit = new QLineEdit(this);
    ipAddressLineEdit->setPlaceholderText("IP Address");
    ipAddressLineEdit->setInputMask("000.000.000.000;_");

    QLineEdit* macAddressLineEdit = new QLineEdit(this);
    macAddressLineEdit->setInputMask("HH:HH:HH:HH:HH:HH;_");

    QDateEdit* dateEdit = new QDateEdit(QDate::currentDate(), this);
    dateEdit->setDisplayFormat("yyyy.MM.dd");

    QFormLayout* formLayout = new QFormLayout(this);
    formLayout->addRow("&IP Addresssss", ipAddressLineEdit);
    formLayout->addRow("&Mac Address", macAddressLineEdit);
    formLayout->addRow("&Date", dateEdit);
}

Widget::~Widget()
{
}

