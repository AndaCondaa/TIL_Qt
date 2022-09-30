#include "breakout.h"
#include <QString>
#include <QLabel>
#include <QApplication>
#include <QAudioOutput>
#include <QMediaPlayer>
#include <QFileInfo>

#define WIDTH 50
#define HEIGHT 12
#define SCR_WIDTH 300
#define SCR_HEIGHT 400

Breakout::Breakout(QWidget *parent)
    : QWidget(parent), xDir(1), yDir(-1)
{
    ball = new Ball(this);
    ball->setGeometry(SCR_WIDTH*0.8, SCR_HEIGHT*0.875, 10, 10);
    //ball->setStyleSheet("QLabel{background-color:red; border-radius: 5px}");

    paddle = new Paddle(this);
    //paddle->setGeometry(SCR_WIDTH*0.7, SCR_HEIGHT*0.9, WIDTH, HEIGHT);
    //paddle->setStyleSheet("QLabel{background-color:black;}");
    paddle->move(SCR_WIDTH*0.7, SCR_HEIGHT*0.9);
    for(int y=0, i=0; y<5; y++)
        for(int x=0; x<6; x++, i++){
            bricks[i] = new Brick(this);
            //bricks[i]->setStyleSheet("QLabel{background-color:cyan;"
            //                         "border:1px solid black}");
            bricks[i]->setGeometry(x*WIDTH, y*HEIGHT+30, WIDTH, HEIGHT);
        }

    resize(SCR_WIDTH, SCR_HEIGHT);

    setMouseTracking(true);

    timerId = startTimer(6);               //QObject의 타이머를 시작

    //점수 표시
    score = new QLabel("0", this);
    score->setGeometry(150, 200, 100, 50);
    score->setAlignment(Qt::AlignHCenter);

    /* 사운드 출력을 위한 미디어 플레이어의 초기화 */
    QAudioOutput *bgAudioOutput = new QAudioOutput;
    bgAudioOutput->setVolume(0.6);
    bgPlayer = new QMediaPlayer( );
    bgPlayer->setAudioOutput(bgAudioOutput);
    bgPlayer->setLoops(QMediaPlayer::Infinite);         /* 무한 반복 */
    bgPlayer->setSource(QUrl::fromLocalFile(QFileInfo("background.mp3").absoluteFilePath()));
    bgPlayer->play( );

    /* 효과음 출력을 위한 플레이어 */
    QAudioOutput *bgEffectOutput = new QAudioOutput;
    bgEffectOutput->setVolume(100);
    effectPlayer = new QMediaPlayer( );
    effectPlayer->setAudioOutput(bgEffectOutput);
    effectPlayer->setLoops(QMediaPlayer::Once);
    effectPlayer->setSource(QUrl::fromLocalFile(QFileInfo("effect.wav").absoluteFilePath( )));

    QAudioOutput *dieEffect = new QAudioOutput;
    dieEffect->setVolume(70);
    diePlayer = new QMediaPlayer( );
    diePlayer->setAudioOutput(dieEffect);
    diePlayer->setLoops(QMediaPlayer::Once);
    diePlayer->setSource(QUrl::fromLocalFile(QFileInfo("die.wav").absoluteFilePath( )));

}

Breakout::~Breakout()
{
    delete ball;
    delete paddle;

    for (int i=0; i<NO_OF_BRICKS; i++){
        delete bricks[i];
    }
}

void Breakout::keyPressEvent(QKeyEvent* e)
{
    int x = paddle->pos().x();
    switch(e->key()){
    case Qt::Key_Left:
        x = (x<=0)?0:paddle->x()-MOVE_SPEED;
        paddle->move(x,paddle->y());
        break;
    case Qt::Key_Right:
        x = (x+WIDTH>=SCR_WIDTH)?SCR_WIDTH-WIDTH:paddle->x()+MOVE_SPEED;
        paddle->move(x,paddle->y());
        break;
    case Qt::Key_Escape:
        qApp->exit();
        break;
    default:
        QWidget::keyPressEvent(e);
    }
}

void Breakout::mouseMoveEvent(QMouseEvent *e)
{
    int x = e->pos().x()-WIDTH/2;
    x = (x<0)?0:(x+WIDTH>width())?width()-WIDTH:x;
    paddle->move(x, paddle->y());
}

void Breakout::timerEvent(QTimerEvent* e)
{
    Q_UNUSED(e);
    moveObjects();
    checkCollision();
}

void Breakout::moveObjects()
{
    ball->move(ball->x()+xDir, ball->y() + yDir);

    if((ball->x()<=0)||(ball->x()+10>=SCR_WIDTH)){
        xDir *= -1;
    }

    if (ball->y()<=0) yDir = 1;
}

void Breakout::checkCollision()
{
    if(ball->geometry().bottom()>height()){
        killTimer(timerId);
        qDebug("Game lost");
        score->setText("낄낄낄낄낄낄낄");
        diePlayer->play();
        bgPlayer->stop();
    }

    //남은 블록이 없으면 게임 종료
    int j = 0;
    for(int i =0; i<NO_OF_BRICKS; i++)
        if(bricks[i]->isHidden()) j++;

    if(j==NO_OF_BRICKS){
        killTimer(timerId);
        qDebug("Victory");
        score->setText("Victory");
    }

    if((ball->geometry()).intersects(paddle->geometry())){
        int paddleLPos = paddle->geometry().left();
        int ballLPos = ball->geometry().left();
        int first = paddleLPos + 8;
        int second = paddleLPos + 16;
        int third = paddleLPos + 24;
        int fourth = paddleLPos + 32;

        if(ballLPos<first) xDir = -1; yDir = -1;
        if(ballLPos>=first && ballLPos < second) xDir = -1; yDir *=-1;
        if(ballLPos>=second && ballLPos < third) xDir = 0; yDir = -1;
        if(ballLPos>=third && ballLPos < fourth) xDir = 1; yDir *= -1;
        if(ballLPos>fourth) xDir = 1; yDir = -1;
    }

    for (int i = 0; i < NO_OF_BRICKS; i++){
        if((ball->geometry()).intersects(bricks[i]->geometry())){
            int ballLeft = ball->geometry().left();
            int ballHeight = ball->geometry().height();
            int ballWidth = ball->geometry().width();
            int ballTop = ball->geometry().top();
            //현재 블록의 위치를 계산
            QPoint pointRight(ballLeft + ballWidth + 1, ballTop);
            QPoint pointLeft(ballLeft -1, ballTop);
            QPoint pointTop(ballLeft, ballTop -1);
            QPoint pointBottom(ballLeft, ballTop + ballHeight + 1);
            if(!bricks[i]->isHidden()){
                if(bricks[i]->geometry().contains(pointRight)) xDir = -1;
                    else if(bricks[i]->geometry().contains(pointLeft)) xDir = 1;
                if(bricks[i]->geometry().contains(pointTop)) yDir = 1;
                    else if(bricks[i]->geometry().contains(pointBottom)) yDir = -1;
                bricks[i]->setHidden(true);
                score_check += 70;
                score->setText(QString::number(score_check));
                //effectPlayer->stop();
                effectPlayer->play();
            }
        }
    }
}
