#ifndef NEWWIDGET_H
#define NEWWIDGET_H

#include <QWidget>


class newWidget : public QWidget
{
    Q_OBJECT

public:
    newWidget(QWidget *parent = nullptr);
    ~newWidget();
};

#endif // NEWWIDGET_H
