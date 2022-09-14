#include <QApplication>
#include <QTextBrowser>
#include <QUrl>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextBrowser *tb = new QTextBrowser();
    tb->resize(700,800);
    tb->setSource(QUrl("index.html"));
    tb->show();

    return a.exec();
}
