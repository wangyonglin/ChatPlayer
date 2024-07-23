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
    explicit SherpaNcnnPlayer(QObject *parent = nullptr);
    bool InitRecognizer();
    QString RunRecognizer(QByteArray &bytes);

private:
    SherpaNcnnQSettings *setting;
    qint32 segment_index = 0;
    float expected_sampling_rate = 16000;
    std::unique_ptr<sherpa_ncnn::Recognizer> recognizer;
    std::unique_ptr<sherpa_ncnn::Stream> stream;

signals:
    void onTalkText(qint32 segment_index,const QString& last_text);
    void finishRecognizer();
};

#endif // SHERPANCNNPLAYER_H
