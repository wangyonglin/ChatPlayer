#include "ASRSpeaker.h"


ASRSpeaker::ASRSpeaker(QObject *parent)
    : QObject{parent}/*,
    sampleRate(16000),
    channelCount(1),
    sampleSize(16)*/
{}
bool ASRSpeaker::InitSpeaker(ASRSettings *setting)
{
    qAudioFormat.setSampleRate(setting->asr_sample_rate);
    qAudioFormat.setChannelCount(setting->asr_channel_count);
    qAudioFormat.setSampleSize(setting->asr_sample_size);
    qAudioFormat.setCodec("audio/pcm");
    qAudioFormat.setByteOrder(QAudioFormat::LittleEndian);
    qAudioFormat.setSampleType(QAudioFormat::SignedInt);

    out = new QAudioOutput(qAudioFormat,this);
    if (!out) {
        return false;
    }

    audioIO = out->start();
    return true;
}


qint64 ASRSpeaker::PlaySpeaker(QByteArray &bytes){
    if(bytes.isEmpty())return 0;
    if(audioIO){
       return audioIO->write((const char*)bytes.data(),bytes.size());
    }
    return 0;
}
