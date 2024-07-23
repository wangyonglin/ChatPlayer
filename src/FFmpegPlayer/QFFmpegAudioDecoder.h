#ifndef QFFMPEGAUDIODECODER_H
#define QFFMPEGAUDIODECODER_H
#include <QPointer>
#include "QFFmpegThreader.h"
#include "QFFmpegRender.h"
#include "QFFmpegPacket.h"
#include "QFFmpegFrame.h"
#include "QFFmpegResampler.h"
#include "QFFmpegManager.h"
class QFFmpegAudioDecoder : public QFFmpegThreader
{
    Q_OBJECT
public:
    explicit QFFmpegAudioDecoder(QObject *parent = nullptr);
    ~QFFmpegAudioDecoder();

   bool frameFinished= true;
private:
    virtual void loopRunnable();
    QFFmpegResampler av_resample;
    QFFmpegRender render;
    QFFmpegManager * manager;
    void BuildDecoder(AVCodecContext *codec_ctx, QFFmpegPacket *pkt_queue, QFFmpegFrame *frame_queue);
public slots:
    virtual void start(Priority pri = InheritPriority);
    virtual void stop();
    virtual void pause();
    virtual void resume();
    void freeParameters(QFFmpegManager * manager);
    QFFmpegManager *initParameters(QFFmpegManager * manager);
};
#endif // QFFMPEGAUDIODECODER_H
