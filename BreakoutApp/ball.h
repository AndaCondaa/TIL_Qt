#ifndef BALL_H
#define BALL_H

#include <QLabel>

class Ball : public QLabel
{
    Q_OBJECT
public:
    explicit Ball(QWidget *parent = nullptr);
};

#endif // BALL_H
