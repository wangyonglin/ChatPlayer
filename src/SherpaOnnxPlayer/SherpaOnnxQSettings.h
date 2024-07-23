#ifndef CONFIGSHERPAONNXPLAYER_H
#define CONFIGSHERPAONNXPLAYER_H

#include <QObject>
#include <QSettings>
#include <QDebug>
#include <QCoreApplication>

class ConfigSherpaOnnxPlayer : public QSettings
{
    Q_OBJECT

public:
    enum StateSherpaOnnxPlayer{none=-1,off,on};
    explicit ConfigSherpaOnnxPlayer(QObject *parent = nullptr);
public:
    //ASR
    int asr_sample_rate;
    int asr_channel_count;
    int asr_sample_size;
    StateSherpaOnnxPlayer asr_speaker_play=off;

    //sherpa_onnx
    int sherpa_onnx_sampling_rate=16000;
    int sherpa_onnx_feature_dim=80;
    int sherpa_onnx_num_threads=4;
    QString sherpa_onnx_encoder="";
    QString sherpa_onnx_decoder="";
    QString sherpa_onnx_joiner="";
    QString sherpa_onnx_tokens="";
    QString sherpa_onnx_keywords="";
    QString sherpa_onnx_provider="cpu";
    int sherpa_onnx_debug=1;
    StateSherpaOnnxPlayer sherpa_onnx_start=off;

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

private:
    StateSherpaOnnxPlayer loadState(const QString &string);
};

#endif // CONFIGSHERPAONNXPLAYER_H
