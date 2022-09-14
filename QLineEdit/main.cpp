#include <QApplication>
#include <QLineEdit>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QLineEdit *lineEdit = new QLineEdit();
    //lineEdit->setEchoMode(QLineEdit::Password);
    lineEdit->setInputMask("999.999.000.009;");
    lineEdit->setPlaceholderText("input the number");
    lineEdit->show();

    return a.exec();
}
