#include "ball.h"

#define RADIUS 20


Ball::Ball(QWidget *parent)
    : QLabel{parent}
{
    resize(RADIUS, RADIUS);
    setPixmap(QPixmap("ball.png"));
}
