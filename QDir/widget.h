#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QDir;
class QListWidget;
class QListWidgetItem;
class QLineEdit;
class QTextEdit;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    void refreshDir();
    QDir *directory;
    QListWidget* dirListWidget;
    QLineEdit* filenameLineEdit;
    QTextEdit* outputEdit;

public slots:
    void selectItem(QListWidgetItem*);      //QListWidget 클릭
    void changeDir();                       //QListWidget 더블클릭
    void makeDir();
    void removeDir();
    void renameDir();
    void copy();
};
#endif // WIDGET_H
