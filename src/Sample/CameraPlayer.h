#ifndef CAMERAPLAYER_H
#define CAMERAPLAYER_H

#include <QWidget>
#include <QCoreApplication>
#include <QCameraInfo>

#include "ASRFramePlayer.h"
#include <QLabel>
#include <QTimer>
#include <QDebug>
#include <QPainter>
#include <QPaintEvent>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>

class QTimer;
class CameraPlayer : public QWidget
{
    Q_OBJECT
public:
    explicit CameraPlayer(QWidget *parent = nullptr);
    bool Play(const QString &name);
    void Stop();
    void InitMatting();
    void InitMatting(cv::Scalar &lowerb, cv::Scalar &upperb);
    void InitMatting(int lowerbbule, int lowerbgreen, int lowerbred, int upperbbule, int upperbgreen, int upperbred);
    void FreeMatting();
    void InitASRFramePlayer(const QRect &rect,int fontsize,const QColor &fontcolor);

    void AddIcon(const QImage &icon);
    QPixmap transFontToPixmap(const QImage &image);
private:

    QLabel *microphone;
    ASRFramePlayer *ASRPlayer;
    std::unique_ptr<cv::VideoCapture> capture;
    QPixmap bufferImage;
    QLabel *label;
    QTimer *timer;
    cv::Scalar  lowerb;
    cv::Scalar  upperb;
    bool bMatteing =false;
    int framepts=0;
    cv::Mat InRangeHSV(cv::Mat &frame, cv::Mat &mask, cv::Scalar &lowerb, cv::Scalar &upperb);
    QImage MattoImage(const cv::Mat &inMat);
    cv::Mat Matting(cv::Mat frame, cv::Mat mask);
    cv::Mat Replace(cv::Mat frame, cv::Mat mask, cv::Mat bg);
    //void refreshFrame();
signals:

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void moveEvent(QMoveEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;
private slots:
    void talkBuffer(QString &msg);
};

#endif // CAMERAPLAYER_H
