#include "SampleWidget.h"
#include <QMessageBox>

SampleWidget::SampleWidget(QWidget *parent)
    : QWidget(parent),
    mSoundThreader(new SoundThreader(this)),
    mBaseSpeaker(new BaseSpeaker(this)),
    mSherpaOnnxPlayer(new SherpaOnnxPlayer(this))
{
    resize(800,600);
    ConfigSherpaOnnxPlayer * setting  =new ConfigSherpaOnnxPlayer(this);
    connect(mSoundThreader,&SoundThreader::UpdateMicrophone,this,&SampleWidget::UpdateMicrophone);

    mBaseSpeaker->InitSpeaker();
    mSoundThreader->loopStart();
    mSherpaOnnxPlayer->InitRecognizer(setting);
}

SampleWidget::~SampleWidget() {
    mSoundThreader->loopStop();
}

void SampleWidget::resizeEvent(QResizeEvent *event)
{
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

void SampleWidget::UpdateMicrophone(QByteArray buffer)
{
   //mBaseSpeaker->PlaySpeaker(buffer);
    QString str= mSherpaOnnxPlayer->RunRecognizer(buffer);
   if(!str.isEmpty()){
       qDebug() << str;
  }
}
