#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QWidget>
#include <QTimer>
#include <QPushButton>


class CustomButton : public QWidget
{
    Q_OBJECT

public:
    CustomButton(QWidget *parent = nullptr);

private:
    bool m_isEntered;
    bool m_isHighlighted;
    QTimer m_timer;
    QPushButton* bt;

protected:
    void paintEvent(QPaintEvent*);
    void enterEvent(QEnterEvent*);
    void leaveEvent(QEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);

signals:
    void clicked();
    void released();
};
#endif // CUSTOMBUTTON_H
