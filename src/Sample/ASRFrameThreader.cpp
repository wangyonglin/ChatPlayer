#include "ASRFrameThreader.h"


ASRFrameThreader::ASRFrameThreader(QObject *parent)
    : BaseThreader{parent},
    sampleRate(16000),
    channelCount(1),
    sampleSize(16)
{
    mSherpaOnnxPlayer= new SherpaOnnxPlayer(this);
    mSherpaNcnnPlayer=new SherpaNcnnPlayer(this);

    mSherpaOnnxPlayer->InitRecognizer();
    mSherpaNcnnPlayer->InitRecognizer();
    Init();
}

ASRFrameThreader::~ASRFrameThreader()
{

}



bool ASRFrameThreader::Init(int sampleRate,
                         int channelCount,
                         int sampleSize){
    qIODevice = nullptr;
    format.setSampleRate(sampleRate);
    format.setChannelCount(channelCount);      // 设定声道数目，mono(平声道)的声道数目是1；stero(立体声)的声道数目是2
    format.setSampleSize(sampleSize);       // 采样位深
    format.setCodec("audio/pcm");   // 设置唯一支持的codec
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);

    QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();
    if (!info.isFormatSupported(format))
    {
        format = info.nearestFormat(format);
    }

    audioInput = new QAudioInput(format,this);
    qIODevice = audioInput->start(); // 这里可以直接写入到文件，咱不用直接就是播放 audioInput->start(file);
    //qIODevice need to manual release, or will memory leak

    if (qIODevice) {
        qDebug() << "device available";
        return true;
    }
    return false;
}

QByteArray ASRFrameThreader::ReadAll(){
    if(qIODevice){

        return qIODevice->readAll();
    }
    return QByteArray();
}

void ASRFrameThreader::loopRunnable()
{
    if(isRunning()){
        QByteArray buffer= ReadAll();
        if(!buffer.isEmpty()){
            if(!bSherpaNcnnPlayer)
            {
                QString talkNameBuffer= mSherpaOnnxPlayer->buildText(buffer);
                if(!talkNameBuffer.isEmpty()){

                    if(QString::localeAwareCompare(talkNameBuffer, tr("小米小米")) == 0){
                        //bNCNNState=true;
                        qDebug() << "语音指令已开启";
                        //emit SendMessageBox(tr("语音指令已开启"));
                        //show();

                    }else{
                        qDebug()<<"字符串不同分支" << talkNameBuffer;
                        //emit talkBuffer(talkNameBuffer);
                    }
                }
            }
            if(bSherpaNcnnPlayer){
                 SherpaNcnnPlayer::ResultText ResultBuffer= mSherpaNcnnPlayer->buildText(buffer);
                //mFrameTextBuffer=ResultBuffer.text;
                if(ResultBuffer.finish){
                    bSherpaNcnnPlayer=false;
                    //hide();
                    qDebug() << "语音指令已关闭";
                    //emit SendMessageBox(tr( "语音指令已关闭"));
                }
            }

        }
    }
}

void ASRFrameThreader::loopStart(Priority pri)
{

    BaseThreader::loopStart(pri);
}

void ASRFrameThreader::loopStop()
{
    qIODevice->close();
    qIODevice=nullptr;
    audioInput->stop();
    BaseThreader::loopStop();
}



