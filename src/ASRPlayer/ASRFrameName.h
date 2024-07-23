#ifndef ASRFRAMENAME_H
#define ASRFRAMENAME_H


#include <QSettings>
#include <QObject>
#include <QDebug>
#include <QDataStream>
#include "sherpa-onnx/csrc/keyword-spotter.h"
#include "ASRSettings.h"
class ASRFrameName : public QObject
{
    Q_OBJECT
public:


    explicit ASRFrameName(QObject *parent = nullptr);

    void BuildRecognizer(QByteArray & bytes);
    bool InitRecognizer(ASRSettings *setting);
signals:
    void finishRecognizer(qint32 id,const QString & name);
private:
    int32_t segment_index=0;
    int32_t expected_sampling_rate=16000;
    std::unique_ptr<sherpa_onnx::KeywordSpotter> kws;
    std::unique_ptr<sherpa_onnx::OnlineStream> kws_stream;
    sherpa_onnx::KeywordSpotterConfig createKeywordSpotter(ASRSettings *setting);
    // int sampling_rate=16000;
    // int feature_dim=80;
    // QString   encoder;
    // QString   decoder;
    // QString   joiner;
    // QString   tokens;
    // int num_threads=4;
    // QString provider;
    // QString keywords;
    // int debug=1;

};

#endif // ASRFRAMENAME_H
