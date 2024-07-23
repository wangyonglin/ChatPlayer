#include "SherpaOnnxPlayer.h"

SherpaOnnxPlayer::SherpaOnnxPlayer(QObject *parent)
    : QObject{parent}
{

}

SherpaOnnxPlayer::~SherpaOnnxPlayer()
{

}


bool SherpaOnnxPlayer::InitRecognizer(ConfigSherpaOnnxPlayer * setting)
{

    sherpa_onnx::KeywordSpotterConfig config= createKeywordSpotter(setting);
    expected_sampling_rate=setting->sherpa_onnx_sampling_rate;
    kws= std::make_unique<sherpa_onnx::KeywordSpotter>(config);
    kws_stream=kws->CreateStream();

    return true;
}

QString SherpaOnnxPlayer::RunRecognizer(QByteArray & bytes)
{
    if(bytes.isEmpty())return QString();
    // 确保data的大小是4的倍数
    if (bytes.size() % sizeof(float) != 0) {
        // 处理错误，例如抛出异常或返回空向量
        return QString();
    }
    std::vector<float> floatVector;
    QDataStream data_stream(bytes);
    data_stream.setByteOrder(QDataStream::LittleEndian);
    while (!data_stream.atEnd()) {
        qint16 sample;
        data_stream >> sample;
        floatVector.push_back(sample);
    }
    std::string last_text;
    //开始推理
    //auto begin = std::chrono::steady_clock::now();
    if (1) {
        kws_stream->AcceptWaveform(expected_sampling_rate, floatVector.data(),floatVector.size());
        // std::vector<float> tail_paddings(static_cast<int>(0.3 * expected_sampling_rate));  // 0.3 seconds at 16 kHz sample rate
        //  stream->AcceptWaveform(expected_sampling_rate, tail_paddings.data(),tail_paddings.size());
        //   kws_stream->InputFinished();
        while (kws->IsReady(kws_stream.get())) {
            kws->DecodeStream(kws_stream.get());
        }
        auto keyword = kws->GetResult(kws_stream.get()).keyword;
        if (!keyword.empty()) {
            //emit finishRecognizer(segment_index,QString::fromStdString(keyword));
            segment_index += 1;
            return QString::fromStdString(keyword);

        }
    }
    return QString();
}
sherpa_onnx::KeywordSpotterConfig SherpaOnnxPlayer:: createKeywordSpotter(ConfigSherpaOnnxPlayer * setting)
{
    sherpa_onnx::FeatureExtractorConfig feat_config;
    feat_config.sampling_rate=setting->sherpa_onnx_sampling_rate;
    feat_config.feature_dim=setting->sherpa_onnx_feature_dim;
    sherpa_onnx::OnlineModelConfig model_config;
    model_config.transducer.encoder=setting->sherpa_onnx_encoder.toStdString();
    model_config.transducer.decoder=setting->sherpa_onnx_decoder.toStdString();
    model_config.transducer.joiner=setting->sherpa_onnx_joiner.toStdString();
    model_config.tokens=setting->sherpa_onnx_tokens.toStdString();
    model_config.num_threads=setting->sherpa_onnx_num_threads;
    model_config.provider=setting->sherpa_onnx_provider.toStdString();
    model_config.debug=setting->sherpa_onnx_debug;

    int32_t max_active_paths = 4;
    int32_t num_trailing_blanks = 1;
    float keywords_score = 1.0;
    float keywords_threshold = 0.25;
    const std::string &keywords_file=setting->sherpa_onnx_keywords.toStdString();
    qDebug() << setting->sherpa_onnx_keywords;
    sherpa_onnx::KeywordSpotterConfig config(feat_config,
                                             model_config,
                                             max_active_paths,
                                             num_trailing_blanks,
                                             keywords_score,
                                             keywords_threshold,
                                             keywords_file);

    return config;
}


