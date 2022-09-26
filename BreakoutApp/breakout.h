#ifndef BREAKOUT_H
#define BREAKOUT_H

#include <QWidget>
#include <QMouseEvent>
#include <QKeyEvent>

class QLabel;
class QMediaPlayer;

class Breakout : public QWidget
{
    Q_OBJECT

public:
    Breakout(QWidget *parent = nullptr);
    ~Breakout();

protected:
    void keyPressEvent(QKeyEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void timerEvent(QTimerEvent*);
    void moveObjects();
    void checkCollision();

    static const int MOVE_SPEED = 10;

private:
    static const int NO_OF_BRICKS = 30;

    QLabel* ball;
    QLabel* paddle;
    QLabel* bricks[NO_OF_BRICKS];
    QLabel* score;
    int score_check = 0;
    QMediaPlayer* bgPlayer;
    QMediaPlayer* effectPlayer;
    QMediaPlayer* diePlayer;


    int timerId;
    int xDir, yDir;
};
#endif // BREAKOUT_H
