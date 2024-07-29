#ifndef BASETHREADER_H
#define BASETHREADER_H

#include <QThread>
#include <QObject>
#include <QDebug>
#include <QMutex>
#include <QWaitCondition>

class BaseThreader : public QThread
{
    Q_OBJECT
public:
    explicit BaseThreader(QObject *parent = nullptr);
    ~BaseThreader() override;
    enum State
    {

        Stoped,     ///<停止状态，包括从未启动过和启动后被停止
        Running,    ///<运行状态
        Paused      ///<暂停状态
    };

    State state() const;

public slots:
   virtual void loopStart(Priority pri = InheritPriority);
    virtual void loopStop();
    virtual void loopPause();
    virtual void loopResume();

protected:
    virtual void run() override final;
    virtual void loopRunnable()=0;
public:
    std::atomic_bool pauseFlag;
    volatile std::atomic_bool stopFlag;
    QMutex mutex;
    QWaitCondition condition;
};

#endif // BASETHREADER_H
