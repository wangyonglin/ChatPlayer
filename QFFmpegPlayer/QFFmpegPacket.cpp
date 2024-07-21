#include "QFFmpegPacket.h"

QFFmpegPacket::QFFmpegPacket(QObject *parent)
    : QObject{parent}
{}
void QFFmpegPacket::enqueue(AVPacket *packet) {
    QMutexLocker locker(&mutex);
    if(packetQueue.size() <= this_maxSize){
        AVPacket *__packet = av_packet_alloc();
        av_packet_move_ref(__packet, packet);
        packetQueue.enqueue(__packet);
        waitCondition.wakeAll();
    }
}

AVPacket* QFFmpegPacket::dequeue() {
    QMutexLocker locker(&mutex);
    while (packetQueue.isEmpty()) {
        waitCondition.wait(&mutex);

    }
    return packetQueue.dequeue();
}

void QFFmpegPacket::clear() {
    QMutexLocker locker(&mutex);
    while (!packetQueue.isEmpty()) {
        AVPacket *frame = packetQueue.dequeue();
        if(frame){
            av_packet_free(&frame); // 释放帧内存
        }
    }
}

int QFFmpegPacket::size()
{
    return packetQueue.size();
}

bool QFFmpegPacket::isEmpty()
{
    return packetQueue.isEmpty();
}

bool QFFmpegPacket::isFulled()
{
    if(!packetQueue.isEmpty()){
        if(packetQueue.size()>=this_maxSize){
            return true;
        }
    }
    return false;
}
