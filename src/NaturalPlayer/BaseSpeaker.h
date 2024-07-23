#ifndef KYLINSPEAKER_H
#define KYLINSPEAKER_H

#include <QObject>
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


class BaseSpeaker : public QObject
{
    Q_OBJECT
public:
    explicit BaseSpeaker(QObject *parent = nullptr);
    ~BaseSpeaker();
    bool InitSpeaker(    int sampleRate=16000,
                     int channelCount=1,
                     int sampleSize=16);
    qint64 PlaySpeaker(QByteArray &bytes);

private:
    QAudioFormat qAudioFormat;
    QAudioOutput *out;
    QIODevice *audioIO;
    QTimer *audioPlayTimer;
    QThread *timerTHread;
    int sampleRate=16000;
    int channelCount=1;
    int sampleSize=16;
};

#endif // KYLINSPEAKER_H
