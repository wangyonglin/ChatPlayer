#ifndef ASRFRAMETHREADER_H
#define ASRFRAMETHREADER_H

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

#include "BaseThreader.h"
#include "SherpaOnnxPlayer.h"
#include "SoundThreader.h"
#include "BaseSpeaker.h"
#include "SherpaNcnnPlayer.h"

class ASRFrameThreader : public BaseThreader
{
    Q_OBJECT
public:
    explicit ASRFrameThreader(QObject *parent = nullptr);
    ~ASRFrameThreader();

private:
    bool Init(int sampleRate=16000,
              int channelCount=1,
              int sampleSize=16);
    QByteArray ReadAll();

signals:
    void UpdateMicrophone(QByteArray buffer);
private: /*   QT audio capture  */
    SherpaOnnxPlayer * mSherpaOnnxPlayer;
    SherpaNcnnPlayer * mSherpaNcnnPlayer;
    bool  bSherpaNcnnPlayer=false;
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

#endif // ASRFRAMETHREADER_H
