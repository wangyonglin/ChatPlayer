#ifndef QFFMPEGPACKET_H
#define QFFMPEGPACKET_H

#include <QQueue>
#include <QMutex>
#include <QWaitCondition>
#include <QDebug>
#include <QThread>

#ifdef __cplusplus
extern "C"
{
#include "libavcodec/avcodec.h"
}
#endif


class QFFmpegPacket : public QObject
{
    Q_OBJECT
public:
    explicit QFFmpegPacket(QObject *parent = nullptr);
    void enqueue(AVPacket *packet);
    AVPacket* dequeue();
    void clear();
    int size();
    bool isEmpty();
    bool isFulled();

private:
    QQueue<AVPacket*> packetQueue;
    QMutex mutex;
    QWaitCondition waitCondition;
    int this_maxSize=100;
};

#endif // QFFMPEGPACKET_H
