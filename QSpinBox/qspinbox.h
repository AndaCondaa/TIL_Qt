#ifndef QSPINBOX_H
#define QSPINBOX_H

#include <QWidget>

class QSpinBox : public QWidget
{
    Q_OBJECT

public:
    QSpinBox(QWidget *parent = nullptr);
    ~QSpinBox();
};
#endif // QSPINBOX_H
