#ifndef ASRMICROPHONE_H
#define ASRMICROPHONE_H

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

class ASRMicrophone : public QObject
{
    Q_OBJECT
public:
    explicit ASRMicrophone(QObject *parent = nullptr);
    ~ASRMicrophone();
    bool InitMicrophone(ASRSettings *setting);

    QByteArray ReadAll();
    QAudioFormat format;



signals:
    void ReadRecording(QByteArray & bytes);
private: /*   QT audio capture  */
    QAudioInput* audioInput;
    QIODevice *qIODevice;
    int sampleRate;
    int channelCount;
    int sampleSize;

};

#endif // ASRMICROPHONE_H
