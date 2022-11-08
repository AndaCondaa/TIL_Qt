#include "widget.h"

#include <QApplication>
#include <QListWidget>
#include <QPushButton>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    QListWidget listWidget(&w);
    for (int var = 1; var <= 9; ++var)
        listWidget.addItem(QString::number(var) + "Item");

    QPushButton b("Change", &w);
    b.move(50, 50);
    QObject::connect(&b, &QPushButton::clicked, [&](){
        QListWidgetItem *item = listWidget.currentItem();
        item->setText("Change");
        item->setForeground(Qt::red);
        item->setBackground(Qt::yellow);
    });

    w.resize(150, 150);
    w.show();
    return a.exec();
}
