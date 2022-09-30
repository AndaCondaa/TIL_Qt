#include "pendulumcontroller.h"

PendulumController::PendulumController(QGraphicsItem* pendulum, QObject *parent)
    : QObject{parent}, m_pendulum(pendulum)
{
    m_timeline.setFrameRange(-90, 90);
    m_timeline.setEasingCurve(QEasingCurve::InOutQuad);
    m_timeline.setDuration(1000);
    m_timeline.setUpdateInterval(16);   //초당 60 프레임 이상 : 기본값은 40(초당 25번)
    connect(&m_timeline, SIGNAL(frameChanged(int)), SLOT(slotRotateItem(int)));
    connect(&m_timeline, SIGNAL(finished()), this,
            SLOT(slotRestartTimeLine()), Qt::QueuedConnection);
    m_timeline.start();
}

void PendulumController::slotRotateItem(int r)
{
    //처음에 -45를 돌려서 그린 후, 그 다음이 -44도를 그려야 하는데
    //-45도 기준으로 -44를 회전하여 그리기 때문에 resetTransform()을 해줌
    //but, 현재는 setTransformOriginPoint() 매서드가 영구적 좌표계 변환인 듯
    m_pendulum->resetTransform();
    m_pendulum->setRotation(r);
}

void PendulumController::slotRestartTimeLine()
{
    m_timeline.toggleDirection();
    m_timeline.start();
}
