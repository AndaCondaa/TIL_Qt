#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QMediaPlayer;
class QAudioOutput;
class QVideoWidget;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QMediaPlayer *m_player;
    QAudioOutput *m_audioOutput;
    QVideoWidget *m_videoWidget;
};
#endif // WIDGET_H
