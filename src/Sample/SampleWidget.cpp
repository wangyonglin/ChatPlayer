#include "SampleWidget.h"
#include <QMessageBox>

SampleWidget::SampleWidget(QWidget *parent)
    : QWidget(parent),
    qASRFramePlayer(new ASRFramePlayer(this))
{


}

SampleWidget::~SampleWidget() {

}

void SampleWidget::resizeEvent(QResizeEvent *event)
{
    qASRFramePlayer->resize(event->size());
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

