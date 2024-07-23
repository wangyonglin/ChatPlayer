#ifndef ASRSPEAKER_H
#define ASRSPEAKER_H
#include <QThread>
#include <QDebug>
#include <QTimer>
#include <QFile>

#include <QAudio>
#include <QAudioFormat>
#include <QAudioInput>
#include <QAudioOutput>
#include <QIODevice>
#include <QAudioFormat>
#include <QAudioInput>
#include <QBuffer>
#include <QByteArray>
#include <QIODevice>
#include <QVector>
#include <QDataStream>
#include <QObject>
#include <QObject>
#include "ASRSettings.h"

class ASRSpeaker : public QObject
{
    Q_OBJECT
public:
    explicit ASRSpeaker(QObject *parent = nullptr);

    bool InitSpeaker(ASRSettings *setting);
    qint64 PlaySpeaker(QByteArray &bytes);

private:
    QAudioFormat qAudioFormat;
    QAudioOutput *out;
    QIODevice *audioIO;
    QTimer *audioPlayTimer;
    QThread *timerTHread;
    // int sampleRate=16000;
    // int channelCount=1;
    // int sampleSize=16;
};

#endif // ASRSPEAKER_H
