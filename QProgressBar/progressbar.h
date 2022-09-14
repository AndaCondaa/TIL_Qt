#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <QWidget>

class ProgressBar : public QWidget
{
    Q_OBJECT

public:
    ProgressBar(QWidget *parent = nullptr);
    ~ProgressBar();
};
#endif // PROGRESSBAR_H
