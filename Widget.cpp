#include "Widget.h"
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent),
    player(new QFFmpegPlayer(this))
{
    resize(800,600);
    player->play("http://vjs.zencdn.net/v/oceans.mp4");
}

Widget::~Widget() {
    player->stop();

    delete player;
}

void Widget::resizeEvent(QResizeEvent *event)
{
    player->resize(event->size());
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        if (QMessageBox::question(this, "退出", "确定要退出吗？", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
            player->stop();
            QApplication::exit();
            event->accept();
        } else {
            event->ignore();
        }
    }else if(event->key() == Qt::Key_F11){
        player->play("http://wangyonglin.oss-cn-shanghai.aliyuncs.com/oceans.mp4");
    }else if(event->key() == Qt::Key_F12){
        player->play("http://wangyonglin.oss-cn-shanghai.aliyuncs.com/405348542-1-16.mp4");
    }else if(event->key() == Qt::Key_F8){
        player->play("http://vjs.zencdn.net/v/oceans.mp4");

    }
}

