// #include "_CameraPlayer.h"
// #include <iostream>
// #include <memory>

// CameraPlayer::CameraPlayer(QWidget *parent)
//     : QWidget{parent},
//     lowerb(cv::Scalar(35, 43, 46)),
//     upperb(cv::Scalar(155, 255, 255)),
//     framepts(60)
// {
//     setAttribute(Qt::WA_TranslucentBackground);
//     label = new QLabel(this);
//     timer = new QTimer(this);
//     // 获取所有可用的摄像头信息
//     QList<QCameraInfo> cameras = QCameraInfo::availableCameras();

//     // 显示摄像头列表
//     foreach (const QCameraInfo &cameraInfo, cameras) {
//         qDebug() << "摄像头名称:" << cameraInfo.deviceName();
//         qDebug() << "摄像头描述:" << cameraInfo.description();
//     }

// }

// void CameraPlayer::InitMatting(cv::Scalar &lowerb, cv::Scalar &upperb)
// {
//     this->lowerb=lowerb;
//     this->upperb=upperb;
//     bMatteing=true;
// }

// void CameraPlayer::InitMatting(int lowerbbule,int lowerbgreen,int lowerbred,
//                              int upperbbule,int upperbgreen,int upperbred)
// {
//     this->lowerb=cv::Scalar(lowerbbule, lowerbgreen, lowerbred);
//     this->upperb=cv::Scalar(upperbbule, upperbgreen, upperbred);
//     bMatteing=true;
// }
// void CameraPlayer::InitMatting()
// {
//     // this->lowerb=cv::Scalar(lowerbbule, lowerbgreen, lowerbred);
//     // this->upperb=cv::Scalar(upperbbule, upperbgreen, upperbred);
//     bMatteing=true;
// }
// void CameraPlayer::FreeMatting()
// {
//     bMatteing=false;
// }
// bool CameraPlayer::Play(const QString &name)
// {
//     capture= std::make_unique<cv::VideoCapture>(name.toUtf8().data());
//     if (!capture->isOpened()) {
//         qFatal("无法打开摄像头");
//         return false;
//     }

//     connect(timer, &QTimer::timeout, [&]() {
//         cv::Mat frame;
//         *capture >> frame; // 从摄像头读取新的帧
//         if(!frame.empty()){
//             if(bMatteing){
//                 cv::Mat hsvframe, mask;
//                // cv::Scalar  lowerb=  cv::Scalar(35, 43, 46);
//                 //cv::Scalar  upperb=  cv::Scalar(155, 255, 255);
//                 hsvframe=InRangeHSV(frame,mask,lowerb,upperb);
//                 cv::Mat matframe= Matting(frame,mask);
//                 QImage image= MattoImage(matframe);
//                 image.scaled(size(), Qt::IgnoreAspectRatio);
//                 bufferImage=QPixmap::fromImage(image);
//                 update();
//             }else{
//                 QImage image= MattoImage(frame);
//                 bufferImage=QPixmap::fromImage(image);
//                 update();
//             }

//         }
//     });
//     timer->start(framepts); // 每秒30帧
//     return true;
// }

// void CameraPlayer::Stop()
// {
//     if(capture){
//         capture->release();
//     }
// }





// void CameraPlayer::paintEvent(QPaintEvent *event)
// {
//     Q_UNUSED(event);
//     QPainter painter(this);
//     painter.drawRect(rect());
//     if(!bufferImage.isNull())
//         painter.drawPixmap(rect(), bufferImage);
// }

// void CameraPlayer::moveEvent(QMoveEvent *event)
// {
//     Q_UNUSED(event);
// }

// void CameraPlayer::resizeEvent(QResizeEvent *event)
// {
//     resize(event->size());
// }
// cv::Mat CameraPlayer::InRangeHSV(cv::Mat &frame,cv::Mat &mask,cv::Scalar & lowerb,cv::Scalar & upperb)
// {
//     cv::Mat hsv;
//     //将每一帧的图像转换到hsv空间
//     cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);
//     //绿幕的颜色范围，将结果存在mask中
//     // cv::inRange(hsv, lowerb,upperb, mask);
//     cv::inRange(hsv, lowerb, upperb, mask);
//     //对mask进行形态学操作
//     //定义一个结构
//     cv::Mat k = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3), cv::Point(-1, -1));
//     //对mask进行形态学闭操作
//     cv::morphologyEx(mask, mask, cv::MORPH_CLOSE, k);
//     cv::erode(mask, mask, k);
//     //高斯模糊
//     cv::GaussianBlur(mask, mask, cv::Size(3, 3), 0, 0);
//     return mask;
// }
// cv::Mat CameraPlayer::Matting(cv::Mat frame, cv::Mat mask)
// {
//     cv::Mat dst = cv::Mat::zeros(frame.size(), CV_8UC4);
//     int dims =  dst.channels();
//     //qDebug() << "######" << dims << "######";
//     for (int i = 0; i < frame.rows; i++)
//     {
//         for (int j = 0; j < frame.cols; j++)
//         {
//             int p = mask.at<uchar>(i, j);  //传入的mask是张二值图,p为当前mask像素值

//             if (p == 0)
//             {   //代表mask此时为前景，将绿幕视频中的前景像素赋给dst
//                 dst.at<cv::Vec4b>(i, j)[0] = frame.at<cv::Vec3b>(i, j)[0];
//                 dst.at<cv::Vec4b>(i, j)[1] = frame.at<cv::Vec3b>(i, j)[1];
//                 dst.at<cv::Vec4b>(i, j)[2] = frame.at<cv::Vec3b>(i, j)[2];
//                 dst.at<cv::Vec4b>(i, j)[3] = 255;
//             } else if(p == 255){
//                 dst.at<cv::Vec4b>(i, j) =  cv::Vec4b(0, 0, 0,0);
//             }
//         }
//     }

//     return dst;
// }

// cv::Mat CameraPlayer::Replace(cv::Mat frame, cv::Mat mask, cv::Mat bg)
// {
//     cv::Mat dst = cv::Mat::zeros(frame.size(), frame.type());

//     for (int i = 0; i < frame.rows; i++)
//     {
//         for (int j = 0; j < frame.cols; j++)
//         {
//             int p = mask.at<uchar>(i, j);  //传入的mask是张二值图,p为当前mask像素值

//             if (p == 0)
//             {   //代表mask此时为前景，将绿幕视频中的前景像素赋给dst
//                 dst.at<cv::Vec3b>(i, j) = frame.at<cv::Vec3b>(i, j);
//             }
//             else if (p == 255)
//             {
//                 //代表mask此时为背景，将背景图像素赋给dst
//                 dst.at<cv::Vec3b>(i, j) = bg.at<cv::Vec3b>(i,j);
//             }

//         }
//     }

//     return dst;
// }

// QImage CameraPlayer::MattoImage(const cv::Mat &inMat)
// {
//     switch (inMat.type()) {
//     // 8-bit, 4 channel
//     case CV_8UC4: {
//         QImage image(inMat.data, inMat.cols, inMat.rows, static_cast<int>(inMat.step), QImage::Format_ARGB32);
//         return image;
//     }
//     // 8-bit, 3 channel
//     case CV_8UC3: {
//         QImage image(inMat.data, inMat.cols, inMat.rows, static_cast<int>(inMat.step), QImage::Format_RGB888);
//         return image.rgbSwapped();
//     }
//     // 8-bit, 1 channel
//     case CV_8UC1: {
//         static QVector<QRgb> sColorTable;
//         // only create our color table once
//         if (sColorTable.isEmpty()) {
//             for (int i = 0; i < 256; ++i) {
//                 sColorTable.push_back(qRgb(i, i, i));
//             }
//         }
//         QImage image(inMat.data, inMat.cols, inMat.rows, static_cast<int>(inMat.step), QImage::Format_Indexed8);
//         image.setColorTable(sColorTable);
//         return image;
//     }
//     default:
//         break;
//     }

//     return QImage();
// }

