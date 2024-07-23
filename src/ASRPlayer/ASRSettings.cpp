#include "ASRSettings.h"

ASRSettings::ASRSettings(QObject *parent)
    : QSettings("/home/wangyonglin/QSpeechRecognizer/conf/kylin.conf", QSettings::IniFormat,parent),
    asr_sample_rate(16000),
    asr_channel_count(1),
    asr_sample_size(16),
    sherpa_onnx_sampling_rate(asr_sample_rate),
    sherpa_onnx_feature_dim(80),
    sherpa_onnx_encoder(""),
    sherpa_onnx_decoder(""),
    sherpa_onnx_joiner(""),
    sherpa_onnx_tokens(""),
    sherpa_onnx_keywords(""),
    sherpa_onnx_num_threads(4),
    sherpa_onnx_provider("cpu"),
    sherpa_onnx_debug(1),
    sherpa_ncnn_sampling_rate(16000),
    sherpa_ncnn_feature_dim(80),
    sherpa_ncnn_rule1_min_trailing_silence(2.4),
    sherpa_ncnn_rule2_min_trailing_silence (1.2),
    sherpa_ncnn_rule3_min_utterance_length(300),
    sherpa_ncnn_tokens(""),
    sherpa_ncnn_encoder_param (""),
    sherpa_ncnn_encoder_bin (""),
    sherpa_ncnn_decoder_param (""),
    sherpa_ncnn_decoder_bin (""),
    sherpa_ncnn_joiner_param (""),
    sherpa_ncnn_joiner_bin (""),
    sherpa_ncnn_method ("greedy_search"),
    sherpa_ncnn_num_threads(4)
{

    //ASR
    asr_sample_rate=value("ASR/sample_rate").toInt();
    asr_channel_count=value("ASR/channel_count").toInt();
    asr_sample_size=value("ASR/sample_size").toInt();
    asr_speaker_play=loadState(value("ASR/speaker_play").toString());

    // qDebug() << "asr_sample_rate:" << asr_sample_rate;
    // qDebug() << "asr_channel_count:" << asr_channel_count;
    // qDebug() << "asr_sample_size:" << asr_sample_size;
    // qDebug() << "asr_speaker_play:" << asr_speaker_play;

    //sherpa_onnx
    sherpa_onnx_sampling_rate=value("SHERPA_ONNX/sampling_rate").toInt();
    sherpa_onnx_feature_dim=value("SHERPA_ONNX/feature_dim").toInt();
    sherpa_onnx_encoder=value("SHERPA_ONNX/encoder").toString();
    sherpa_onnx_decoder=value("SHERPA_ONNX/decoder").toString();
    sherpa_onnx_joiner=value("SHERPA_ONNX/joiner").toString();
    sherpa_onnx_tokens=value("SHERPA_ONNX/tokens").toString();
    sherpa_onnx_num_threads=value("SHERPA_ONNX/num_threads").toInt();
    sherpa_onnx_provider=value("SHERPA_ONNX/provider").toString();
    sherpa_onnx_debug=value("SHERPA_ONNX/debug").toInt();
    sherpa_onnx_keywords=value("SHERPA_ONNX/keywords").toString();
    sherpa_onnx_start=loadState(value("SHERPA_ONNX/start").toString());

    // qDebug() << "sherpa_onnx_sampling_rate:" << sherpa_onnx_sampling_rate;
    // qDebug() << "sherpa_onnx_feature_dim:" << sherpa_onnx_feature_dim;
    // qDebug() << "sherpa_onnx_encoder:" << sherpa_onnx_encoder;
    // qDebug() << "sherpa_onnx_decoder:" << sherpa_onnx_decoder;
    // qDebug() << "sherpa_onnx_joiner:" << sherpa_onnx_joiner;
    // qDebug() << "sherpa_onnx_tokens:" << sherpa_onnx_tokens;
    // qDebug() << "sherpa_onnx_keywords:" << sherpa_onnx_keywords;
    // qDebug() << "sherpa_onnx_provider:" << sherpa_onnx_provider;
    // qDebug() << "sherpa_onnx_num_threads:" << sherpa_onnx_num_threads;
    // qDebug() << "sherpa_onnx_debug:" << sherpa_onnx_debug;
    // qDebug() << "sherpa_onnx_start:" << sherpa_onnx_start;

    sherpa_ncnn_sampling_rate==value("SHERPA_NCNN/sampling_rate").toInt();
    sherpa_ncnn_feature_dim=value("SHERPA_NCNN/feature_dim").toInt();
    sherpa_ncnn_rule1_min_trailing_silence=value("SHERPA_NCNN/rule1_min_trailing_silence").toFloat();
    sherpa_ncnn_rule2_min_trailing_silence=value("SHERPA_NCNN/rule2_min_trailing_silence").toFloat();
    sherpa_ncnn_rule3_min_utterance_length=value("SHERPA_NCNN/rule3_min_utterance_length").toInt();
    sherpa_ncnn_tokens=value("SHERPA_NCNN/tokens").toString();
    sherpa_ncnn_encoder_param = value("SHERPA_NCNN/encoder_param").toString();
    sherpa_ncnn_encoder_bin = value("SHERPA_NCNN/encoder_bin").toString();
    sherpa_ncnn_decoder_param = value("SHERPA_NCNN/decoder_param").toString();
    sherpa_ncnn_decoder_bin = value("SHERPA_NCNN/decoder_bin").toString();
    sherpa_ncnn_joiner_param = value("SHERPA_NCNN/joiner_param").toString();
    sherpa_ncnn_joiner_bin = value("SHERPA_NCNN/joiner_bin").toString();
    sherpa_ncnn_method =value("SHERPA_NCNN/method").toString();
    sherpa_ncnn_num_threads=value("SHERPA_NCNN/num_threads").toInt();


    // qDebug() << "sherpa_ncnn_sampling_rate:" << sherpa_ncnn_sampling_rate;
    // qDebug() << "sherpa_ncnn_feature_dim:" << sherpa_ncnn_feature_dim;
    // qDebug() << "sherpa_ncnn_rule1_min_trailing_silence:" << sherpa_ncnn_rule1_min_trailing_silence;
    // qDebug() << "sherpa_ncnn_rule2_min_trailing_silence:" << sherpa_ncnn_rule2_min_trailing_silence;
    // qDebug() << "sherpa_ncnn_rule3_min_utterance_length:" << sherpa_ncnn_rule3_min_utterance_length;
    // qDebug() << "sherpa_ncnn_tokens:" << sherpa_ncnn_tokens;
    // qDebug() << "sherpa_ncnn_encoder_param:" << sherpa_ncnn_encoder_param;
    // qDebug() << "sherpa_ncnn_encoder_bin:" << sherpa_ncnn_encoder_bin;
    // qDebug() << "sherpa_ncnn_decoder_param:" << sherpa_ncnn_decoder_param;
    // qDebug() << "sherpa_ncnn_decoder_bin:" << sherpa_ncnn_decoder_bin;
    // qDebug() << "sherpa_ncnn_joiner_param:" << sherpa_ncnn_joiner_param;
    // qDebug() << "sherpa_ncnn_joiner_bin:" << sherpa_ncnn_joiner_bin;
    // qDebug() << "sherpa_ncnn_method:" << sherpa_ncnn_method;
    // qDebug() << "sherpa_ncnn_num_threads:" << sherpa_ncnn_num_threads;

}

ASRSettings::ASRState ASRSettings::loadState(const QString &string)
{
    if((string == QString::fromLocal8Bit("on")) || (string== QString::fromLocal8Bit("ON")) || (string== QString::fromLocal8Bit("On")))
    {
        return on;
    }else if ((string == QString::fromLocal8Bit("off")) || (string== QString::fromLocal8Bit("OFF")) || (string== QString::fromLocal8Bit("Off"))){
        return off;
    }
    return none;
}

