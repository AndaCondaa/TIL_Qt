#include "pendulumcontroller.h"
#include "pendulumitem.h"

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsScene>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsView* view = new QGraphicsView;
    QGraphicsScene* scene = new QGraphicsScene(view);
    view->setScene(scene);

    PendulumItem* pendulum = new PendulumItem;
    scene->addItem(pendulum);
    PendulumController controller(pendulum);
    view->setRenderHint(QPainter::Antialiasing);
    view->setSceneRect(-150, -20, 300, 200);    //중간에 씬을 두려고 함, 그래서 씬 위치 고정
    view->resize(320, 240);
    view->show();

    return a.exec();
}
