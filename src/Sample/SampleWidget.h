#ifndef SAMPLEWIDGET_H
#define SAMPLEWIDGET_H

#include <QWidget>
#include <QKeyEvent>
#include <QApplication>

#include "QFFmpegPlayer.h"
#include "ASRFramePlayer.h"



class SampleWidget : public QWidget
{
    Q_OBJECT

public:
    SampleWidget(QWidget *parent = nullptr);
    ~SampleWidget();
private:
    QFFmpegPlayer *qFFmpegPlayer;
    ASRFramePlayer * qASRFramePlayer;
    void resizeEvent(QResizeEvent *event);
    void keyPressEvent(QKeyEvent *event);
};
#endif // SAMPLEWIDGET_H
