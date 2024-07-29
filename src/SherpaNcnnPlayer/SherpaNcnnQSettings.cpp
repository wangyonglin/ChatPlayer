#include "SherpaNcnnQSettings.h"

SherpaNcnnQSettings::SherpaNcnnQSettings(QObject *parent)
    : QBootstrap("/home/wangyonglin/QSpeechRecognizer/conf/kylin.conf",parent),
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
}
