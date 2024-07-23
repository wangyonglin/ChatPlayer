#include "ASRMicrophone.h"

ASRMicrophone::ASRMicrophone(QObject *parent)
    : QObject{parent},
    sampleRate(16000),
    channelCount(1),
    sampleSize(16)
{

}

ASRMicrophone::~ASRMicrophone()
{

}

bool ASRMicrophone::InitMicrophone(ASRSettings *setting){
    qIODevice = nullptr;
    format.setSampleRate(setting->asr_sample_rate);
    format.setChannelCount(setting->asr_channel_count);      // 设定声道数目，mono(平声道)的声道数目是1；stero(立体声)的声道数目是2
    format.setSampleSize(setting->asr_sample_size);       // 采样位深
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

QByteArray ASRMicrophone::ReadAll(){
    if(qIODevice){
        return qIODevice->readAll();
    }
    return QByteArray();
}


