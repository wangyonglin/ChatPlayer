#include "SampleWidget.h"
#include <QMessageBox>

SampleWidget::SampleWidget(QWidget *parent)
    : QWidget(parent),
    qFFmpegPlayer(new QFFmpegPlayer(this)),
    qASRFramePlayer(new ASRFramePlayer(this)),
    qCameraPlayer(new CameraPlayer(this))
{

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(qFFmpegPlayer);
    layout->addWidget(qCameraPlayer);
    setLayout(layout);
    qFFmpegPlayer->play("/home/wangyonglin/视频/405348542-1-16.mp4");
    //qCameraPlayer->InitMatting(35, 43, 46,155, 255, 255);
    qCameraPlayer->Play("/dev/video0");

}

SampleWidget::~SampleWidget() {

}

void SampleWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setBrush(Qt::red);
    painter.drawRect(rect());

}

void SampleWidget::resizeEvent(QResizeEvent *event)
{
    qASRFramePlayer->resize(event->size());
    qFFmpegPlayer->resize(event->size().width(),event->size().height()/2);
    qCameraPlayer->resize(event->size().width(),event->size().height()/2);
}

void SampleWidget::keyPressEvent(QKeyEvent *event)
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

