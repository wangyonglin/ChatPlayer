#ifndef ASRTHREADER_H
#define ASRTHREADER_H


#include <QObject>
#include "ASRMicrophone.h"
#include "QThreader.h"
#include "ASRSpeaker.h"
#include "ASRFrameName.h"
#include "ASRFrameText.h"
#include "ASRSettings.h"

class ASRThreader: public QThreader
{
    Q_OBJECT
public:
    explicit ASRThreader(QObject *parent = nullptr);
    void InitThreader(ASRSettings *setting=nullptr);
    virtual void loopStart(Priority pri = InheritPriority);
    virtual void loopStop();
    QVector<QString> listText;
private:
    ASRMicrophone *asrMicrophone=nullptr;
    ASRFrameName *asrFrameName=nullptr;
    ASRFrameText *asrFrameText=nullptr;
    ASRSpeaker *asrSpeaker=nullptr;
    ASRSettings *setting;
    bool bRecognizer=false;

private:
    virtual void loopRunnable();
signals:
    void finishRecognizer();
    void updateRecognizer();
};

#endif // ASRTHREADER_H
