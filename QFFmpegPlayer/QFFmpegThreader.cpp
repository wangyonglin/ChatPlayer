#include "QFFmpegThreader.h"

QFFmpegThreader::QFFmpegThreader(QObject *parent)
    : QThread(parent),
    pauseFlag(false),
    stopFlag(false)
{}

QFFmpegThreader::~QFFmpegThreader()
{

}

QFFmpegThreader::State QFFmpegThreader::state() const
{
    State s = Stoped;
    if (!QThread::isRunning())
    {
        s = Stoped;
    }
    else if (QThread::isRunning() && pauseFlag)
    {
        s = Paused;
    }
    else if (QThread::isRunning() && (!pauseFlag))
    {
        s = Running;
    }
    return s;
}

void QFFmpegThreader::start(Priority pri)
{
    QThread::start(pri);
}

void QFFmpegThreader::stop()
{
    if (QThread::isRunning())
    {
        stopFlag = true;
        condition.wakeAll();
        QThread::quit();
        QThread::wait();
    }
}

void QFFmpegThreader::pause()
{
    if (QThread::isRunning())
    {
        pauseFlag = true;
    }
}

void QFFmpegThreader::resume()
{
    if (QThread::isRunning())
    {
        pauseFlag = false;
        condition.wakeAll();
    }
}

void QFFmpegThreader::run()
{
    qDebug() << "enter thread : " << QThread::currentThreadId();
    while (!stopFlag)
    {

        loopRunnable(); // do something...

        if (pauseFlag)
        {
            mutex.lock();
            condition.wait(&mutex);
            mutex.unlock();
        }
    }
    pauseFlag = false;
    stopFlag = false;

    qDebug() << "exit thread : " << QThread::currentThreadId();
}
