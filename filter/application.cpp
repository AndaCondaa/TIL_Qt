#include "application.h"
#include "widget.h"

Application::Application(int& argc, char** argv) : QApplication(argc, argv)
{
}

bool Application::notify(QObject* receiver, QEvent *e)
{
    qDebug() << "Application : notify called :" << e->type();

    if(e->type() == QEvent::MouseButtonPress) {
        qDebug() << "Application : mouse event";
        return false;       // event를 ignore해라는 말.
    }

    Widget* obj = dynamic_cast<Widget*>(receiver);
     if(obj != nullptr) {       // Widget과 관련된 Object라면 여기로 들어간다.
         qDebug() << "Cast successful :" << obj->metaObject()->className();
     } else {
         qDebug() << "Cast failed";
     }

    return QApplication::notify(receiver, e);
}





