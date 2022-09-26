#ifndef BRICK_H
#define BRICK_H

#include <QLabel>

class Brick : public QLabel
{
    Q_OBJECT
public:
    explicit Brick(QWidget *parent = nullptr);
};

#endif // BRICK_H
