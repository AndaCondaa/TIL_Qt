#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QString>
#include <QCompleter>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget w;

    QLineEdit *lineEdit1 = new QLineEdit(&w);
    lineEdit1->setEchoMode(QLineEdit::Normal);
    lineEdit1->setPlaceholderText("아이디를 입력하세요.");
    lineEdit1->setMaxLength(20);
    lineEdit1->setGeometry(10,50,300,30);

    QLineEdit *lineEdit2 = new QLineEdit(&w);
    lineEdit2->setEchoMode(QLineEdit::Password);
    lineEdit2->setMaxLength(20);
    lineEdit2->setGeometry(10,90,300,30);

    QLabel *label = new QLabel("asdfasdf", &w);
    label->setGeometry(10,10,300,30);

    QObject::connect(lineEdit2, SIGNAL(textEdited(const QString&)),
                     label, SLOT(setText(const QString &)));

    QStringList CompletionList;
    CompletionList << "babo" <<"bart"<<"keroro"<<"bread"<<"kukukuru";
    QCompleter* StringCompleter = new QCompleter(CompletionList, lineEdit1);
    StringCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    lineEdit1->setCompleter(StringCompleter);

    w.show();
    return a.exec();
}
