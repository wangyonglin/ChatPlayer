#ifndef SHERPANCNNQSETTINGS_H
#define SHERPANCNNQSETTINGS_H

#include <QObject>
#include <QSettings>
#include "QBootstrap.h"

class SherpaNcnnQSettings : public QBootstrap
{
    Q_OBJECT
public:
    explicit SherpaNcnnQSettings(QObject *parent = nullptr);

public:
    //sherpa_ncnn
    int sherpa_ncnn_sampling_rate=16000;
    int sherpa_ncnn_feature_dim=80;
    float sherpa_ncnn_rule1_min_trailing_silence = 2.4;
    float sherpa_ncnn_rule2_min_trailing_silence = 1.2;
    int sherpa_ncnn_rule3_min_utterance_length = 300;
    int sherpa_ncnn_num_threads=4;

    QString sherpa_ncnn_tokens = "";
    QString sherpa_ncnn_encoder_param = "";
    QString sherpa_ncnn_encoder_bin = "";
    QString sherpa_ncnn_decoder_param = "";
    QString  sherpa_ncnn_decoder_bin = "";
    QString sherpa_ncnn_joiner_param = "";
    QString sherpa_ncnn_joiner_bin = "";
    QString sherpa_ncnn_method ="greedy_search";
};

#endif // SHERPANCNNQSETTINGS_H
