#ifndef QFFMPEGPLAYER_H
#define QFFMPEGPLAYER_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QOpenGLShader>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>

#include "QFFmpegAudioDecoder.h"
#include "QFFmpegRender.h"

#include <QWidget>
#include <QObject>
#include <QString>
#include "QFFmpegDemuxer.h"
#include "QFFmpegVideoDecoder.h"

class QFFmpegPlayer : public QOpenGLWidget,public QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:

    explicit QFFmpegPlayer(QWidget *parent = nullptr);
    ~QFFmpegPlayer();

    void play(const QString &url);
    void stop();


private:
    QFFmpegDemuxer *av_demux;
    QFFmpegAudioDecoder *audio_dec;
    QFFmpegVideoDecoder *video_dec;
    QFFmpegManager * manager;
    //shader程序
    QOpenGLShaderProgram m_program;
    QOpenGLBuffer vbo;
    int idY,idU,idV;
    int width,height;
    uchar* ptr;
    QImage imageUpdate;
signals:
    void start(QFFmpegThreader::Priority pri = QFFmpegThreader::InheritPriority);
    void finished();
    // QOpenGLWidget interface
protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void paintGL() override;
};

#endif // QFFMPEGPLAYER_H
