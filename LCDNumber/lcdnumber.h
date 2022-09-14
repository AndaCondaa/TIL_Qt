#ifndef LCDNUMBER_H
#define LCDNUMBER_H

#include <QWidget>

class LCDNumber : public QWidget
{
    Q_OBJECT

public:
    LCDNumber(QWidget *parent = nullptr);
    ~LCDNumber();
};
#endif // LCDNUMBER_H
