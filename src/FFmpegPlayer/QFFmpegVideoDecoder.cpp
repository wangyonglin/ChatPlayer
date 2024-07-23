#include "QFFmpegVideoDecoder.h"

QFFmpegVideoDecoder::QFFmpegVideoDecoder(QObject *parent)
    : QFFmpegThreader{parent}
{}

QFFmpegManager *QFFmpegVideoDecoder::initParameters( QFFmpegManager * manager){
    manager->video_codec_ctx = avcodec_alloc_context3(NULL);
    if(!  manager->video_codec_ctx)return nullptr;
    int read_ret = avcodec_parameters_to_context(  manager->video_codec_ctx, manager->video_codecpar);
    if(read_ret < 0) {
        char errmsg[AV_ERROR_MAX_STRING_SIZE];
        av_make_error_string(errmsg,AV_ERROR_MAX_STRING_SIZE, read_ret);
        qDebug() << "avcodec_parameters_to_context failed" << errmsg;
        avcodec_free_context(&  manager->video_codec_ctx);
        return nullptr;
    }
    // h264
    //h264_qsv  AV_CODEC_ID_H264
     //  avcodec_find_decoder_by_name()

       // if(AV_CODEC_ID_H264 == manager->video_codec_ctx->codec_id)
       //    manager-> codec = avcodec_find_decoder_by_name("h264_qsv");
       // else
        manager->codec = avcodec_find_decoder(  manager->video_codec_ctx->codec_id); //作业： 硬件解码
    if(!manager->codec) {
        qDebug() << "avcodec_find_decoder failed";
        avcodec_free_context(&  manager->video_codec_ctx);
        return nullptr;
    }

    read_ret = avcodec_open2(  manager->video_codec_ctx, manager->codec, NULL);
    if(read_ret < 0) {
        char errmsg[AV_ERROR_MAX_STRING_SIZE];
        av_make_error_string(errmsg,AV_ERROR_MAX_STRING_SIZE, read_ret);
        qDebug() << "avcodec_open2 failed" << errmsg;
        avcodec_free_context(&  manager->video_codec_ctx);
        return nullptr;
    }
    manager->YUV420BufferSize = av_image_get_buffer_size(
        AV_PIX_FMT_YUV420P,
        manager->video_codec_ctx->width,
        manager->video_codec_ctx->height,1);
    if(manager->YUV420Buffer){
        av_free( manager->YUV420Buffer);
        manager->YUV420Buffer=nullptr;
    }
    manager->YUV420Buffer = (unsigned char *)av_malloc(manager->YUV420BufferSize*sizeof(uchar));



    emit sigFirst( manager->YUV420Buffer,manager->video_codec_ctx->width,manager->video_codec_ctx->height);
    this->manager=manager;
    return  manager;
}

void QFFmpegVideoDecoder::freeParameters(QFFmpegManager * manager){
    if( manager->video_codec_ctx){
        avcodec_free_context(& manager->video_codec_ctx);
        manager->video_codec_ctx=nullptr;
    }
}

void QFFmpegVideoDecoder::loopRunnable()
{

    if(state()==Running && !frameFinished){
        if (manager->get_video_synchronize() > manager->get_master_synchronize())
        {
             QThread::usleep(10);
            return;
        }

        if(!manager->video_pkt_queue->isEmpty()){
            if(manager->video_frame_queue->size()  <10){
                BuildDecoder(manager->video_codec_ctx,manager->video_pkt_queue,manager->video_frame_queue);
            }else{
                QThread::usleep(200);
                return;
            }
        }

        if(!manager->video_frame_queue->isEmpty()){
            AVFrame * yuvFrame= manager->video_frame_queue->dequeue();
            if(yuvFrame){
               int64_t pts_time= (yuvFrame->pts == AV_NOPTS_VALUE) ? NAN : yuvFrame->pts;
                manager->video_synchronize(pts_time,manager->video_pts_begin,manager->video_pts_base);
                int bytes =0;
                for(int i=0;i<manager->video_codec_ctx->height;i++){
                    memcpy( manager->YUV420Buffer+bytes,yuvFrame->data[0]+yuvFrame->linesize[0]*i,manager->video_codec_ctx->width);
                    bytes+=manager->video_codec_ctx->width;
                }

                int u=manager->video_codec_ctx->height>>1;
                for(int i=0;i<u;i++){
                    memcpy( manager->YUV420Buffer+bytes,yuvFrame->data[1]+yuvFrame->linesize[1]*i,manager->video_codec_ctx->width/2);
                    bytes+=manager->video_codec_ctx->width/2;
                }

                for(int i=0;i<u;i++){
                    memcpy( manager->YUV420Buffer+bytes,yuvFrame->data[2]+yuvFrame->linesize[2]*i,manager->video_codec_ctx->width/2);
                    bytes+=manager->video_codec_ctx->width/2;
                }

                emit newFrame();
                av_frame_free(&yuvFrame);
            }

        }
    }
}

void QFFmpegVideoDecoder::start(Priority pri)
{
    QFFmpegThreader::start(pri);
}

void QFFmpegVideoDecoder::stop()
{
    QFFmpegThreader::stop();
}

void QFFmpegVideoDecoder::pause()
{
    QFFmpegThreader::pause();
}

void QFFmpegVideoDecoder::resume()
{
    QFFmpegThreader::resume();
}

void QFFmpegVideoDecoder::BuildDecoder(AVCodecContext *codec_ctx,QFFmpegPacket *pkt_queue, QFFmpegFrame *frame_queue)
{
    if(!codec_ctx)return;
    if(pkt_queue->isEmpty())return;
    AVPacket * pkt= pkt_queue->dequeue();
    if(!pkt)return;
    int ret = avcodec_send_packet(codec_ctx, pkt);
    av_packet_free(&pkt);
    if (ret < 0)
    {
        char errmsg[AV_ERROR_MAX_STRING_SIZE];
        av_make_error_string(errmsg,AV_ERROR_MAX_STRING_SIZE, ret);
        qDebug() << "avcodec_send_packet failed" << errmsg;
        return ;
    }
    AVFrame* frame = av_frame_alloc();
    if(!frame)return;
    ret = avcodec_receive_frame(codec_ctx, frame);
    if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF){
        return ;
    }else if (ret < 0) {
        char errmsg[AV_ERROR_MAX_STRING_SIZE];
        av_make_error_string(errmsg,AV_ERROR_MAX_STRING_SIZE, ret);
        qDebug() << "avcodec_receive_frame failed" << errmsg;
        return ;
    }
    frame_queue->enqueue(frame);
    av_frame_free(&frame);
}

