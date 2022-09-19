#ifndef QTEDITOR_H
#define QTEDITOR_H

#include <QMainWindow>

class QLabel;
class QAction;
class QMdiArea;

class QtEditor : public QMainWindow
{
    Q_OBJECT

public:
    QtEditor(QWidget *parent = nullptr);
    ~QtEditor();

public slots:
    void newFile();
    void openFile();
    void saveFile();
    void saveAsFile();
    void printFile();

    void alignText();
    void editText();

private:
    QLabel* statusLabel;
    QMdiArea* mdiArea;

    template <typename T>
    QAction* makeAction(QString icon, QString text, T shortCut,
                        QString toolTip, QObject* recv, const char* slot);

    template <typename T, typename Functor>
    QAction* makeAction(QString icon, QString text, T shortCut,
                        QString toolTip, Functor lambda);
};
#endif // QTEDITOR_H
