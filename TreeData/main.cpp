#include <QApplication>
#include <QTreeWidget>
#include <QTreeWidgetItem>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTreeWidget treeWidget;
    treeWidget.setColumnCount(2);
    treeWidget.setHeaderLabels(QStringList() << "Col One" << "Col Two");

    for (int i = 0; i < 3; i++) {
        QTreeWidgetItem *pItem = new QTreeWidgetItem(&treeWidget);
        pItem->setText(0, QString::number(i));
        pItem->setText(1, "Hello");
        for(int j = 0; j < 3; j++) {
            QTreeWidgetItem *item = new QTreeWidgetItem(pItem);
            item->setText(0, QString::number(j));
            item->setText(1, "worle");

        }
    }


    return a.exec();
}
