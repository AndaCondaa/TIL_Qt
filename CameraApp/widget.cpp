#include "widget.h"

#include <QCamera>
#include <QImageCapture>
#include <QMediaRecorder>
#include <QMediaDevices>
#include <QMediaCaptureSession>
#include <QAudioInput>
#include <QAudioDevice>
#include <QMediaDevices>
#include <QMediaFormat>
#include <QVideoFrame>
#include <QVideoWidget>
#include <QUrl>
#include <QFileInfo>
#include <QPushButton>
#include <QBoxLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    const QList<QCameraDevice> cameras = QMediaDevices::videoInputs( );
    for (const QCameraDevice &cameraDevice : cameras) {
        qDebug( ) << cameraDevice.description( );
    }

    camera = new QCamera(QMediaDevices::defaultVideoInput( ));
    camera->setCustomFocusPoint(QPointF(0.25f, 0.75f));
    if(camera != nullptr) {
        QVideoWidget *preview = new QVideoWidget(this);
        preview->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        preview->setMinimumSize(720, 400);

        imageCapture = new QImageCapture( );

        QMediaFormat format;
        format.setFileFormat(QMediaFormat::AAC);
        format.setAudioCodec(QMediaFormat::AudioCodec::AAC);

        QFile::remove((QFileInfo("sample.mp4").absoluteFilePath( )));
        recorder = new QMediaRecorder(camera);
        recorder->setQuality(QMediaRecorder::HighQuality);
        recorder->setOutputLocation(QUrl(QFileInfo("sample.mp4").absoluteFilePath( )));
        recorder->setMediaFormat(format);
        recorder->setAudioSampleRate(44100);
        recorder->setAudioBitRate(0);
        recorder->setAudioChannelCount(2);

        QMediaCaptureSession* captureSession = new QMediaCaptureSession;
        captureSession->setCamera(camera);
        captureSession->setImageCapture(imageCapture);
        captureSession->setRecorder(recorder);
        captureSession->setVideoOutput(preview);

        QAudioInput* audioInput= new QAudioInput(this);
        audioInput->setDevice(QMediaDevices::defaultAudioInput());
        for (const QAudioDevice &deviceInfo : QMediaDevices::audioInputs()) {
            qDebug() << "Device: " << deviceInfo.description();
        }
        audioInput->setVolume(100.0);
        captureSession->setAudioInput(audioInput);

        QPushButton* imageButton = new QPushButton("Image", this);
        connect(imageButton, SIGNAL(clicked( )), SLOT(captureImage( )));
        QPushButton* videoButton = new QPushButton("Record", this);
        videoButton->setCheckable(true);
        connect(videoButton, SIGNAL(toggled(bool)), SLOT(recordVideo(bool)));

        QHBoxLayout* hboxLayout = new QHBoxLayout;
        hboxLayout->addWidget(imageButton);
        hboxLayout->addWidget(videoButton);

        QVBoxLayout* mainLayout = new QVBoxLayout(this);
        mainLayout->addWidget(preview);
        mainLayout->addLayout(hboxLayout);

        camera->start( ); // 카메라의 프리뷰 시작
        preview->resize(preview->sizeHint( ));
    }
}

Widget::~Widget()
{
    camera->stop();
}

void Widget::captureImage( ) {
    imageCapture->captureToFile(QFileInfo("capture.jpg").absoluteFilePath( ));
}

void Widget::recordVideo(bool isToggle) {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    button->setText(isToggle?"Stop":"Record");
    isToggle?recorder->record( ):recorder->stop();
}
