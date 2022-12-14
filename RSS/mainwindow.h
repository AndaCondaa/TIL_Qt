#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QNetworkReply>
#include <QListView>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void openRssFeed();
    void replyFinished(QNetworkReply*);

private:
    QComboBox *combo;
    QNetworkAccessManager *manager;

    QNetworkReply *reply;
};

class ListView : public QListView {
    Q_OBJECT

protected:
    void keyPressEvent(QKeyEvent *envet);
};

#endif // MAINWINDOW_H
