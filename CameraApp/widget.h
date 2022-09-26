#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QCamera;
class QImageCapture;
class QMediaRecorder;
class QVideoFrame;
class QMediaCaptureSession;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QCamera* camera;
    QImageCapture* imageCapture;
    QMediaRecorder* recorder;
    QMediaCaptureSession* captureSession;

private slots:
    void captureImage( );
    void recordVideo(bool);
};
#endif // WIDGET_H
