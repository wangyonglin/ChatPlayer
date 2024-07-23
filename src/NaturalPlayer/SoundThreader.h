#ifndef KYLINMICROPHONE_H
#define KYLINMICROPHONE_H

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
#include <QObject>
#include "BaseThreader.h"
class SoundThreader : public BaseThreader
{
    Q_OBJECT
public:
    explicit SoundThreader(QObject *parent = nullptr);
    ~SoundThreader();
    bool Init(int sampleRate=16000,
                        int channelCount=1,
                        int sampleSize=16);
    QByteArray ReadAll();

signals:
    void UpdateMicrophone(QByteArray buffer);
private: /*   QT audio capture  */
    QAudioFormat format;
    QAudioInput* audioInput;
    QIODevice *qIODevice;
    int sampleRate;
    int channelCount;
    int sampleSize;

    // BaseThreader interface

protected:
    virtual void loopRunnable() override;

    // BaseThreader interface
public slots:
    virtual void loopStart(Priority pri = InheritPriority) override;

    // BaseThreader interface
public slots:
    virtual void loopStop() override;
};

#endif // KYLINMICROPHONE_H
