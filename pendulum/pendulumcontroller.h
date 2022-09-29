#ifndef PENDULUMCONTROLLER_H
#define PENDULUMCONTROLLER_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimeLine>

class PendulumController : public QObject
{
    Q_OBJECT
public:
    explicit PendulumController(QGraphicsItem* pendulum,
                                QObject *parent = nullptr);
private slots:
    void slotRotateItem(int r);
    void slotRestartTimeLine();
private:
    QTimeLine m_timeline;
    QGraphicsItem* m_pendulum;

};

#endif // PENDULUMCONTROLLER_H
