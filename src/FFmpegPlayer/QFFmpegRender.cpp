#include "QFFmpegRender.h"

QFFmpegRender::QFFmpegRender(QObject *parent)
    : QObject{parent}
{

}

QFFmpegRender::~QFFmpegRender()
{

}



void QFFmpegRender::InitFormat(int dst_nb_samples, int rate, int sample_size, int nch)
{

    QAudioFormat format;
    format.setSampleRate(rate); // 采样率
    format.setChannelCount(nch);   // 声道数
    format.setSampleSize(sample_size);    // 采样大小
    format.setCodec("audio/pcm"); // 音频编码格式
    format.setByteOrder(QAudioFormat::LittleEndian); // 字节顺序
    format.setSampleType(QAudioFormat::SignedInt);  // 采样类型

    int len = dst_nb_samples * format.channelCount() * format.sampleSize()/8;
    Q_UNUSED(len);
    // 创建 QAudioOutput 对象
    audioOutput = new QAudioOutput(format);
    //audioOutput->setBufferSize(len * 100);
    audioOutput->setVolume(1.0); // 设置音量（0.0 - 1.0）

    // 打开音频输出
    outputDevice = audioOutput->start();
}

void QFFmpegRender::WriteOutput(const char *data, qint64 len)
{
    outputDevice->write(data, len);

}
void QFFmpegRender::WriteOutput(QByteArray bytes){
    if(!bytes.isEmpty())
        outputDevice->write(bytes.data(), bytes.length());
}
void QFFmpegRender::FreeFormat()
{
     audioOutput->stop();
}



