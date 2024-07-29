#ifndef SAMPLEWIDGET_H
#define SAMPLEWIDGET_H

#include <QWidget>
#include <QKeyEvent>
#include <QApplication>

#include "QFFmpegPlayer.h"
#include "ASRFramePlayer.h"
#include "CameraPlayer.h"


class SampleWidget : public QWidget
{
    Q_OBJECT

public:
    SampleWidget(QWidget *parent = nullptr);
    ~SampleWidget();
private:
    CameraPlayer *qCameraPlayer;
    QFFmpegPlayer *qFFmpegPlayer;
    ASRFramePlayer * qASRFramePlayer;


    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
};
#endif // SAMPLEWIDGET_H
