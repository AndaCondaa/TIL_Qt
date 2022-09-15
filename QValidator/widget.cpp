#include "widget.h"
#include <QLabel>
#include <QLineEdit>
#include <QValidator>
#include <QFormLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QDoubleValidator* doubleValidator = new QDoubleValidator(this);
//    doubleValidator->setRange(10.0, 100.0, 3);
    doubleValidator->setBottom(10.0);
    doubleValidator->setTop(100.0);
    doubleValidator->setDecimals(3);

    QIntValidator* intValidator = new QIntValidator(this);
//    intValidator->setRange(13, 19);
    intValidator->setBottom(13);
    intValidator->setTop(19);

    QRegularExpressionValidator* rEV = new QRegularExpressionValidator(this);
    rEV->setRegularExpression(
                QRegularExpression("^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
                                   "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
                                   "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
                                   "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$"));

    QLineEdit* lED = new QLineEdit(this);
    lED->setValidator(doubleValidator);

    QLineEdit* lEI = new QLineEdit(this);
    lEI->setValidator(intValidator);

    QLineEdit* lER = new QLineEdit(this);
    lER->setValidator(rEV);

    QFormLayout* formLayout = new QFormLayout(this);
    formLayout->addRow("&Double", lED);
    formLayout->addRow("&Int", lEI);
    formLayout->addRow("&Regular Expression", lER);

    setWindowTitle("Validator");






}

Widget::~Widget()
{
}

