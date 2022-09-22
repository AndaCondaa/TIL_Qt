#ifndef BREAKOUT_H
#define BREAKOUT_H

#include <QWidget>
#include <QMouseEvent>
#include <QKeyEvent>

class QLabel;


class Breakout : public QWidget
{
    Q_OBJECT

public:
    Breakout(QWidget *parent = nullptr);
    ~Breakout();

private:
    static const int NO_OF_BRICKS = 30;

    QLabel* ball;
    QLabel* paddle;
    QLabel* bricks[NO_OF_BRICKS];

protected:
    void keyPressEvent(QKeyEvent*);
    void mouseMoveEvent(QMouseEvent*);

    static const int MOVE_SPEED = 20;
};
#endif // BREAKOUT_H
