#ifndef SHERPAONNXPLAYER_H
#define SHERPAONNXPLAYER_H

#include <QObject>
#include <QLabel>
#include <QWidget>
#include <QPainter>
#include <QHBoxLayout>
#include <QPainterPath>
#include <QSettings>

#include "sherpa-onnx/csrc/keyword-spotter.h"
#include "SherpaOnnxQSettings.h"
#include "BaseThreader.h"
#include "SoundThreader.h"

class SherpaOnnxPlayer : public QObject
{
    Q_OBJECT
public:
    explicit SherpaOnnxPlayer(QObject *parent = nullptr);
    ~SherpaOnnxPlayer();
    QString buildText(const QByteArray & bytes);
    bool InitRecognizer();

signals:
    void finishRecognizer(qint32 id,const QString & name);

private:
    SherpaOnnxQSettings * setting;
    int32_t segment_index=0;
    int32_t expected_sampling_rate=16000;
    std::unique_ptr<sherpa_onnx::KeywordSpotter> kws;
    std::unique_ptr<sherpa_onnx::OnlineStream> kws_stream;
    sherpa_onnx::KeywordSpotterConfig createKeywordSpotter();
};

#endif // SHERPAONNXPLAYER_H
