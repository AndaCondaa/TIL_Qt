#include <QApplication>
#include <QTime>
#include <QTimeEdit>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTimeEdit* timeEdit = new QTimeEdit(0);
    timeEdit->setTime(QTime::currentTime());
    timeEdit->show();

    QDateEdit* dateEdit = new QDateEdit(QDate::currentDate(), 0);
    dateEdit->setCalendarPopup(true);
    dateEdit->show();

    return a.exec();
}
