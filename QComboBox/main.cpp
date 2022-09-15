#include <QApplication>
#include <QComboBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QComboBox *comboBox = new QComboBox();
    comboBox->addItem("KDE");
    comboBox->addItem("Gnome");
    comboBox->addItem("FVWM");
    comboBox->addItem("CDE");
    comboBox->setEditable(true);            //enter 입력 시, 옵션 추가
    comboBox->show();

    return a.exec();
}
