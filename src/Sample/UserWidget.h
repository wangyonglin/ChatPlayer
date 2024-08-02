#ifndef USERWIDGET_H
#define USERWIDGET_H

#include <QWidget>
#include <QKeyEvent>
#include <QApplication>

#include "QFFmpegPlayer.h"
#include "CameraPlayer.h"
#include "MaskPlayer.h"

class UserWidget : public QWidget
{
    Q_OBJECT

public:
    UserWidget(QWidget *parent = nullptr);
    ~UserWidget();
private:
    CameraPlayer *qCameraPlayer;
    QFFmpegPlayer *qFFmpegPlayer;
    MaskPlayer * qMaskPlayer;


    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
};
#endif // USERWIDGET_H
