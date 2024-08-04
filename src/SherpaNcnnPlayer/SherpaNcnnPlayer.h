#ifndef SHERPANCNNPLAYER_H
#define SHERPANCNNPLAYER_H

#include <QObject>

#include "sherpa-ncnn/csrc/recognizer.h"
#include <QObject>
#include <QDebug>
#include <QDataStream>
#include <QBuffer>
#include <QResizeEvent>
#include <SherpaNcnnQSettings.h>

class SherpaNcnnPlayer : public QObject
{
    Q_OBJECT
public:
    typedef struct ResultText{
        bool finish=false;
        QString text;
    }ResultText;
public:
    explicit SherpaNcnnPlayer(QObject *parent = nullptr);
    bool InitRecognizer();
    ResultText buildText(QByteArray &bytes);

    ResultText buildResultText(bool finish=false,const QString & text="");
private:
    SherpaNcnnQSettings *setting;
    qint32 segment_index = 0;
    float expected_sampling_rate = 16000;
    std::unique_ptr<sherpa_ncnn::Recognizer> recognizer;
    std::unique_ptr<sherpa_ncnn::Stream> stream;

signals:
    void onTalkText(qint32 segment_index,const QString& last_text);
    void onTalkFinish(const QString& last_text);
};

#endif // SHERPANCNNPLAYER_H
