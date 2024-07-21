#ifndef QFFMPEGMANAGER_H
#define QFFMPEGMANAGER_H

extern "C" {
#include <libavutil/pixfmt.h>
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavutil/avutil.h"
#include "libswscale/swscale.h"
#include "libavutil/imgutils.h"
#include <libavutil/opt.h>
#include <libavutil/channel_layout.h>
#include <libavutil/samplefmt.h>
#include <libavutil/time.h>
#include <libswresample/swresample.h>
}

#include <QWidget>
#include "QFFmpegPacket.h"
#include "QFFmpegFrame.h"
#include "QFFmpegSynchronizer.h"

class QFFmpegManager : public QFFmpegSynchronizer
{
    Q_OBJECT
public:
    explicit QFFmpegManager(QWidget *parent = nullptr);
public:
    QFFmpegPacket *audio_pkt_queue=nullptr;
    QFFmpegPacket *video_pkt_queue=nullptr;
    QFFmpegFrame *audio_frame_queue=nullptr;
    QFFmpegFrame *video_frame_queue=nullptr;
    const    AVCodec * codec=nullptr;
    QString url;
    AVFormatContext *ifmt_ctx=nullptr;
    int audio_stream_index=-1;
    int video_stream_index=-1;
    AVCodecParameters * audio_codecpar=nullptr;
    AVCodecParameters * video_codecpar=nullptr;
    AVRational video_pts_base = {0,0};
    AVRational audio_pts_base = {0,0};
    int64_t audio_pts_begin = 0;
    int64_t video_pts_begin = 0;
    AVCodecContext *audio_codec_ctx=nullptr;
    AVCodecContext * video_codec_ctx=nullptr;
    struct SwrContext *swr_ctx;
    int64_t dst_ch_layout =AV_CH_LAYOUT_STEREO;
    int dst_rate=44100;
    enum AVSampleFormat dst_sample_fmt=AV_SAMPLE_FMT_S16;
    uint8_t** src_data_;
    uint8_t** dst_data_;
    int src_nb_channels, dst_nb_channels;
    int src_linesize, dst_linesize;
    int src_nb_samples_, dst_nb_samples_;
    enum AVSampleFormat dst_sample_fmt_;
    enum AVSampleFormat src_sample_fmt_;
    int data_size=0;
    //Video Readerer
    int YUV420BufferSize=0;
    uchar *YUV420Buffer= nullptr;
    bool isFirst = true;
private:
    QMutex mutex;
    QWaitCondition waitCondition;
};

#endif // QFFMPEGMANAGER_H
