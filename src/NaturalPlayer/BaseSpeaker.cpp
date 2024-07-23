#include "BaseSpeaker.h"



BaseSpeaker::BaseSpeaker(QObject *parent)
    : QObject{parent},
    sampleRate(16000),
    channelCount(1),
    sampleSize(16)
{}

BaseSpeaker::~BaseSpeaker()
{
    //if(out)
      //  out->stop();
}

bool BaseSpeaker::InitSpeaker(int sampleRate, int channelCount, int sampleSize)
{
    qAudioFormat.setSampleRate(sampleRate);
    qAudioFormat.setChannelCount(channelCount);
    qAudioFormat.setSampleSize(sampleSize);
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


qint64 BaseSpeaker::PlaySpeaker(QByteArray &bytes){
    if(bytes.isEmpty())return 0;
    if(audioIO){
        return audioIO->write((const char*)bytes.data(),bytes.size());
    }
    return 0;
}
