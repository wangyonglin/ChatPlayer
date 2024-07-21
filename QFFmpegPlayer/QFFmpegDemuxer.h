#ifndef QFFMPEGDEMUXER_H
#define QFFMPEGDEMUXER_H
#include "QFFmpegThreader.h"
#include <QObject>

#include "QFFmpegManager.h"
class QFFmpegDemuxer : public QFFmpegThreader
{
    Q_OBJECT
public:
    explicit QFFmpegDemuxer(QObject *parent = nullptr);

public:
    bool frameFinished=true;
    QFFmpegManager*manager;
public slots:
    virtual void start(Priority pri = InheritPriority);
    virtual void stop();
    virtual void pause();
    virtual void resume();
    QFFmpegManager* initParameters(QFFmpegManager *controller);
    void freeParameters(QFFmpegManager *controller);
private:
    virtual void loopRunnable() Q_DECL_OVERRIDE;
signals:
    void demuxFinished();
};

#endif // QFFMPEGDEMUXER_H
