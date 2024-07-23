#ifndef QFFMPEGVIDEODECODER_H
#define QFFMPEGVIDEODECODER_H

#include <QObject>
#include "QFFmpegThreader.h"
#include "QFFmpegManager.h"

class QFFmpegVideoDecoder : public QFFmpegThreader
{
    Q_OBJECT
public:
    explicit QFFmpegVideoDecoder(QObject *parent = nullptr);
    bool frameFinished= true;
private:
    virtual void loopRunnable();
    QFFmpegManager * manager;
    AVFrame         *yuvFrame     = NULL;
    void BuildDecoder(AVCodecContext *codec_ctx, QFFmpegPacket *pkt_queue, QFFmpegFrame *frame_queue);
public slots:
    virtual void start(Priority pri = InheritPriority);
    virtual void stop();
    virtual void pause();
    virtual void resume();
    void freeParameters( QFFmpegManager * controller);
    QFFmpegManager *initParameters( QFFmpegManager * controller);
signals:
    void drawImage(const QImage &image);
    void sigFirst(uchar* p,int w,int h);
    void newFrame();
};

#endif // QFFMPEGVIDEODECODER_H
