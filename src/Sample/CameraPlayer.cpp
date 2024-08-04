#include "CameraPlayer.h"
#include <iostream>
#include <memory>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>

CameraPlayer::CameraPlayer(QWidget *parent)
    : QWidget{parent},
    lowerb(cv::Scalar(35, 43, 46)),
    upperb(cv::Scalar(155, 255, 255)),
    framepts(60)//,

{

    setAttribute(Qt::WA_TranslucentBackground);
    timer = new QTimer(this);

    QHBoxLayout *iconlayout = new QHBoxLayout(this);
    microphone = new QLabel(this);
    microphone->setPixmap(transFontToPixmap(QImage(tr(":/images/iconfont/microphone.png"))));
    microphone->setContentsMargins(5,5,5,5);
    iconlayout->addWidget(microphone);
    iconlayout->setAlignment(Qt::AlignRight|Qt::AlignTop);
    setLayout(iconlayout);

    microphone->hide();
}
QPixmap CameraPlayer::transFontToPixmap(const QImage & image)
{
    QImage scaledImage =image.scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    return QPixmap::fromImage(scaledImage);
}
void CameraPlayer::InitMatting(cv::Scalar &lowerb, cv::Scalar &upperb)
{
    this->lowerb=lowerb;
    this->upperb=upperb;
    bMatteing=true;
}

void CameraPlayer::InitMatting(int lowerbbule,int lowerbgreen,int lowerbred,
                             int upperbbule,int upperbgreen,int upperbred)
{
    this->lowerb=cv::Scalar(lowerbbule, lowerbgreen, lowerbred);
    this->upperb=cv::Scalar(upperbbule, upperbgreen, upperbred);
    bMatteing=true;
}
void CameraPlayer::InitMatting()
{
    // this->lowerb=cv::Scalar(lowerbbule, lowerbgreen, lowerbred);
    // this->upperb=cv::Scalar(upperbbule, upperbgreen, upperbred);
    bMatteing=true;
}
void CameraPlayer::FreeMatting()
{
    bMatteing=false;
}
bool CameraPlayer::Play(const QString &name)
{
    capture= std::make_unique<cv::VideoCapture>(name.toUtf8().data());
    if (!capture->isOpened()) {
        qFatal("无法打开摄像头");
        return false;
    }

    connect(timer, &QTimer::timeout, [&]() {
        cv::Mat frame;
        *capture >> frame; // 从摄像头读取新的帧
        if(!frame.empty()){
            if(bMatteing){
                cv::Mat hsvframe, mask;
               // cv::Scalar  lowerb=  cv::Scalar(35, 43, 46);
                //cv::Scalar  upperb=  cv::Scalar(155, 255, 255);
                hsvframe=InRangeHSV(frame,mask,lowerb,upperb);
                cv::Mat matframe= Matting(frame,mask);
                QImage image= MattoImage(matframe);
                image.scaled(size(), Qt::IgnoreAspectRatio);
                bufferImage=QPixmap::fromImage(image);
                update();
            }else{
                QImage image= MattoImage(frame);
                bufferImage=QPixmap::fromImage(image);
                update();
            }

        }
    });
    timer->start(framepts); // 每秒30帧
    return true;
}

void CameraPlayer::Stop()
{
    if(capture){
        capture->release();
    }
}

void CameraPlayer::InitASRFramePlayer(const QRect &rect,int fontsize,const QColor &fontcolor)
{
    ASRPlayer=new ASRFramePlayer(this);


        ASRPlayer->setGeometry(rect);
        ASRPlayer->setFontSize(fontsize);
        ASRPlayer->setFontColor(fontcolor);
        QVBoxLayout * mainlayout= new QVBoxLayout(ASRPlayer);
        mainlayout->addWidget(ASRPlayer);
        setLayout(mainlayout);
        connect(ASRPlayer,&ASRFramePlayer::SendMessageBox,[=](const QString & msg){
            if(QString::localeAwareCompare(msg, tr("语音指令已开启")) == 0){
                microphone->show();
                qDebug() << "语音指令已开启";
            }else  if(QString::localeAwareCompare(msg, tr("语音指令已关闭")) == 0){
                microphone->hide();
                qDebug() << "语音指令已关闭";
            }

        });


}





void CameraPlayer::talkBuffer(QString & msg)
{

}



void CameraPlayer::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QFont font;
    font.setBold(true);
    font.setPointSize(12);
    QPen pen;
    pen.setWidth(2); // 设置描边的宽度
    pen.setColor(Qt::red); // 设置描边的颜色
    QPainter painter(this);
    painter.setFont(font);
    painter.setPen(pen);
    painter.drawRect(rect());
    if(!bufferImage.isNull())
        painter.drawPixmap(rect(), bufferImage);

}

void CameraPlayer::moveEvent(QMoveEvent *event)
{
    Q_UNUSED(event);
}

void CameraPlayer::resizeEvent(QResizeEvent *event)
{
    resize(event->size());

}
cv::Mat CameraPlayer::InRangeHSV(cv::Mat &frame,cv::Mat &mask,cv::Scalar & lowerb,cv::Scalar & upperb)
{
    cv::Mat hsv;
    //将每一帧的图像转换到hsv空间
    cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);
    //绿幕的颜色范围，将结果存在mask中
    // cv::inRange(hsv, lowerb,upperb, mask);
    cv::inRange(hsv, lowerb, upperb, mask);
    //对mask进行形态学操作
    //定义一个结构
    cv::Mat k = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3), cv::Point(-1, -1));
    //对mask进行形态学闭操作
    cv::morphologyEx(mask, mask, cv::MORPH_CLOSE, k);
    cv::erode(mask, mask, k);
    //高斯模糊
    cv::GaussianBlur(mask, mask, cv::Size(3, 3), 0, 0);
    return mask;
}
cv::Mat CameraPlayer::Matting(cv::Mat frame, cv::Mat mask)
{
    cv::Mat dst = cv::Mat::zeros(frame.size(), CV_8UC4);
    int dims =  dst.channels();
    //qDebug() << "######" << dims << "######";
    for (int i = 0; i < frame.rows; i++)
    {
        for (int j = 0; j < frame.cols; j++)
        {
            int p = mask.at<uchar>(i, j);  //传入的mask是张二值图,p为当前mask像素值

            if (p == 0)
            {   //代表mask此时为前景，将绿幕视频中的前景像素赋给dst
                dst.at<cv::Vec4b>(i, j)[0] = frame.at<cv::Vec3b>(i, j)[0];
                dst.at<cv::Vec4b>(i, j)[1] = frame.at<cv::Vec3b>(i, j)[1];
                dst.at<cv::Vec4b>(i, j)[2] = frame.at<cv::Vec3b>(i, j)[2];
                dst.at<cv::Vec4b>(i, j)[3] = 255;
            } else if(p == 255){
                dst.at<cv::Vec4b>(i, j) =  cv::Vec4b(0, 0, 0,0);
            }
        }
    }

    return dst;
}

cv::Mat CameraPlayer::Replace(cv::Mat frame, cv::Mat mask, cv::Mat bg)
{
    cv::Mat dst = cv::Mat::zeros(frame.size(), frame.type());

    for (int i = 0; i < frame.rows; i++)
    {
        for (int j = 0; j < frame.cols; j++)
        {
            int p = mask.at<uchar>(i, j);  //传入的mask是张二值图,p为当前mask像素值

            if (p == 0)
            {   //代表mask此时为前景，将绿幕视频中的前景像素赋给dst
                dst.at<cv::Vec3b>(i, j) = frame.at<cv::Vec3b>(i, j);
            }
            else if (p == 255)
            {
                //代表mask此时为背景，将背景图像素赋给dst
                dst.at<cv::Vec3b>(i, j) = bg.at<cv::Vec3b>(i,j);
            }

        }
    }

    return dst;
}

QImage CameraPlayer::MattoImage(const cv::Mat &inMat)
{
    switch (inMat.type()) {
    // 8-bit, 4 channel
    case CV_8UC4: {
        QImage image(inMat.data, inMat.cols, inMat.rows, static_cast<int>(inMat.step), QImage::Format_ARGB32);
        return image;
    }
    // 8-bit, 3 channel
    case CV_8UC3: {
        QImage image(inMat.data, inMat.cols, inMat.rows, static_cast<int>(inMat.step), QImage::Format_RGB888);
        return image.rgbSwapped();
    }
    // 8-bit, 1 channel
    case CV_8UC1: {
        static QVector<QRgb> sColorTable;
        // only create our color table once
        if (sColorTable.isEmpty()) {
            for (int i = 0; i < 256; ++i) {
                sColorTable.push_back(qRgb(i, i, i));
            }
        }
        QImage image(inMat.data, inMat.cols, inMat.rows, static_cast<int>(inMat.step), QImage::Format_Indexed8);
        image.setColorTable(sColorTable);
        return image;
    }
    default:
        break;
    }

    return QImage();
}

