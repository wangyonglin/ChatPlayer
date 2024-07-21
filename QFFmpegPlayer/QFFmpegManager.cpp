#include "QFFmpegManager.h"

QFFmpegManager::QFFmpegManager(QWidget *parent)
    : QFFmpegSynchronizer{parent},

    audio_pkt_queue(new QFFmpegPacket(this)),
    video_pkt_queue(new QFFmpegPacket(this)),
    audio_frame_queue(new QFFmpegFrame(this)),
    video_frame_queue(new QFFmpegFrame(this))
{}
