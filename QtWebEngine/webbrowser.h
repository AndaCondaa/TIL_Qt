#ifndef WEBBROWSER_H
#define WEBBROWSER_H

#include <QMainWindow>
#include <QtWebEngineWidgets>


class QLineEdit;

class WebBrowser : public QMainWindow
{
    Q_OBJECT
public:
    explicit WebBrowser(QWidget *parent = nullptr);

private:
    QLineEdit *lineEditURL;
    QWebEngineView *webEngineView;

public:
    void goSlot();
    void goBackwardSlot();
    void goForwardSlot();
    void goHomeSlot();
};

#endif // WEBBROWSER_H
