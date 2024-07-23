#ifndef QFFMPEGSYNCHRONIZER_H
#define QFFMPEGSYNCHRONIZER_H

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
#include <QMutex>
#include <QWaitCondition>
#include <iostream>
#include <chrono>

class QFFmpegSynchronizer : public QWidget
{
    Q_OBJECT
public:
    explicit QFFmpegSynchronizer(QWidget *parent = nullptr);


    void init_synchronize();
    int64_t get_master_synchronize();
    void start_synchronize();
    void audio_synchronize(int64_t  pts_time, int64_t start_time, AVRational timebase);
    void video_synchronize(int64_t  pts_time, int64_t start_time, AVRational timebase);
    int64_t get_audio_synchronize();
    int64_t get_video_synchronize();
private:
    int64_t __audio_pts_time=0;
    int64_t __video_pts_time=0;
    bool __locktime_root_flag =false;
    int64_t __locktime_start_time_ms =0;
    QMutex mutex;
    QWaitCondition waitCondition;
    int64_t get_now_ms();
};

#endif // QFFMPEGSYNCHRONIZER_H
