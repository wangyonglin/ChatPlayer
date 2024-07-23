#ifndef ASRFRAMETEXT_H
#define ASRFRAMETEXT_H

#include "sherpa-ncnn/csrc/recognizer.h"
#include <QObject>
#include <QDebug>
#include <QDataStream>
#include <QBuffer>
#include <QResizeEvent>
#include "ASRSettings.h"



class ASRFrameText : public QObject
{
    Q_OBJECT
public:
    explicit ASRFrameText(QObject *parent = nullptr);
    bool InitRecognizer(ASRSettings *setting);
    QString BuildRecognizer(QByteArray &bytes);

private:
    ASRSettings *setting;
    qint32 segment_index = 0;
    float expected_sampling_rate = 16000;
    std::unique_ptr<sherpa_ncnn::Recognizer> recognizer;
    std::unique_ptr<sherpa_ncnn::Stream> stream;

signals:
    void onTalkText(qint32 segment_index,const QString& last_text);
    void finishRecognizer();
};

#endif // ASRFRAMETEXT_H
