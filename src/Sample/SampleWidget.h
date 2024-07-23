#ifndef SAMPLEWIDGET_H
#define SAMPLEWIDGET_H

#include <QWidget>
#include <QKeyEvent>
#include <QApplication>

#include "QFFmpegPlayer.h"
#include "SherpaOnnxPlayer.h"
#include "SoundThreader.h"
#include "BaseSpeaker.h"


class SampleWidget : public QWidget
{
    Q_OBJECT

public:
    SampleWidget(QWidget *parent = nullptr);
    ~SampleWidget();
private slots:
    void UpdateMicrophone(QByteArray buffer);
private:
    ConfigSherpaOnnxPlayer *config;

    SoundThreader * mSoundThreader;
    BaseSpeaker * mBaseSpeaker;
    QFFmpegPlayer *qFFmpegPlayer;
    SherpaOnnxPlayer * mSherpaOnnxPlayer;
    void resizeEvent(QResizeEvent *event);
    void keyPressEvent(QKeyEvent *event);
};
#endif // SAMPLEWIDGET_H
