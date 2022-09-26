#include "widget.h"

#include <QMediaPlayer>
#include <QAudioOutput>
#include <QVideoWidget>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    m_videoWidget = new QVideoWidget(this);
    m_videoWidget->resize(QSize(1600,1200));
    m_videoWidget->setAspectRatioMode(Qt::IgnoreAspectRatio);

    m_audioOutput = new QAudioOutput(this);
    m_audioOutput->setVolume(100);

    m_player = new QMediaPlayer(this);
    m_player->setPlaybackRate(1);
    m_player->setVideoOutput(m_videoWidget);
    m_player->setAudioOutput(m_audioOutput);
    m_player->setSource(QUrl("http://commondatastorage.googleapis.com/gtv-videos-bucket/sample/TearsOfSteel.mp4"));

    m_player->play();
}

Widget::~Widget()
{
}

