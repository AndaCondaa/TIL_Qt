#include "custombutton.h"
#include <QPainter>

CustomButton::CustomButton(QWidget *parent)
    : QWidget(parent), m_isEntered(false), m_isHighlighted(false)
{
    resize(500,300);
}

void CustomButton::paintEvent(QPaintEvent*)
{
    QPainter painter;
    painter.begin(this);
    painter.setBrush(m_isHighlighted?(Qt::yellow):
                                     (m_isEntered)?(Qt::darkYellow):(Qt::lightGray));
    painter.drawRoundedRect(this->rect(),15,15);
    painter.drawText(10,20,QString("x: %1 / y: %2").arg(x()).arg(y()));
    painter.end();

    //클릭시 하이라이트 상태-> 선택된 상태로
    if(m_isHighlighted){
        m_timer.stop();
        m_timer.singleShot(300, this, SLOT(update()));
        m_isHighlighted = false;
    }
}

//Rollover 버튼의 구현
void CustomButton::enterEvent(QEnterEvent*)
{
    m_isEntered = true;
    m_isHighlighted = false;
    update();
}

void CustomButton::leaveEvent(QEvent*)
{
    m_isEntered = false;
    m_isHighlighted = false;
    repaint();
}

//버튼을 누르면 clicked() 시그널 발생
void CustomButton::mousePressEvent(QMouseEvent*)
{
    //m_isEntered = false;
    m_isHighlighted = true;
    update();
    emit clicked();
}

void CustomButton::mouseReleaseEvent(QMouseEvent*)
{
    emit released();
}
