#include "UserWidget.h"
#include <QMessageBox>
#include <QStackedWidget>
#include <QSplitter>
#include <QPixmap>
UserWidget::UserWidget(QWidget *parent)
    : QWidget(parent),
    qGamePlayer(new GamePlayer(this)),
    qFFmpegPlayer(new QFFmpegPlayer(this)),
    qCameraPlayer(new CameraPlayer(this)),
    qMaskPlayer(new MaskPlayer(qFFmpegPlayer))

{
    setAutoFillBackground(true);
    qGamePlayer->resize(480,854);
    qGamePlayer->raise();
    qGamePlayer->Play("ddddd");
    qFFmpegPlayer->setStyleSheet("QFFmpegPlayer { min-width: 480px; min-height: 480px; }");

    qCameraPlayer->setStyleSheet("CameraPlayer { min-width: 480px; min-height: 374px; }");
    qCameraPlayer->InitASRFramePlayer(QRect(0,120,480,360),26,QColor(255,255,255));

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(0);
    layout->setMargin(0);
    layout->addWidget(qFFmpegPlayer);
    layout->addWidget(qCameraPlayer);
    setLayout(layout);

    qFFmpegPlayer->play("/home/wangyonglin/视频/405348542-1-16.mp4");
    //qCameraPlayer->InitMatting(35, 43, 46,155, 255, 255);
    qCameraPlayer->Play("/dev/video0");


}

UserWidget::~UserWidget() {

}

void UserWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setBrush(Qt::black);
    QPixmap pixmap(":/images/edddc90e94c3e353638759be1d29bb4e.jpeg"); // 替换为你的图片路径
    painter.drawPixmap(rect(),pixmap);

}

void UserWidget::resizeEvent(QResizeEvent *event)
{
    qFFmpegPlayer->resize(480,480);
    qMaskPlayer->resize(480,480);
    qGamePlayer->resize(480,854);
}

void UserWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        if (QMessageBox::question(this, "退出", "确定要退出吗？", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {


            QApplication::exit();
        //    event->accept();
        } else {
         //   event->ignore();
        }
    }else if(event->key() == Qt::Key_F11){
    }else if(event->key() == Qt::Key_F12){
    }else if(event->key() == Qt::Key_F8){
    }
}

