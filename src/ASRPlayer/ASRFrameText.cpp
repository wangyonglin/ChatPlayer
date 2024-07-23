#include "ASRFrameText.h"

ASRFrameText::ASRFrameText(QObject *parent)
    : QObject{parent},
    expected_sampling_rate(16000)

{}



bool ASRFrameText::InitRecognizer(ASRSettings *asr_setting)
{
    setting=asr_setting;
    sherpa_ncnn::RecognizerConfig config;
    //初始化默认配置
    expected_sampling_rate=setting->sherpa_ncnn_sampling_rate;
    config.model_config.encoder_opt.num_threads = setting->sherpa_ncnn_num_threads;
    config.model_config.decoder_opt.num_threads = setting->sherpa_ncnn_num_threads;
    config.model_config.joiner_opt.num_threads = setting->sherpa_ncnn_num_threads;
    qDebug() << "sherpa_ncnn_sampling_rate:" << setting->sherpa_ncnn_sampling_rate;
    config.enable_endpoint = true;
    config.endpoint_config.rule1.min_trailing_silence = setting->sherpa_ncnn_rule1_min_trailing_silence;
    config.endpoint_config.rule2.min_trailing_silence = setting->sherpa_ncnn_rule2_min_trailing_silence;
    config.endpoint_config.rule3.min_utterance_length = setting->sherpa_ncnn_rule3_min_utterance_length;

    config.feat_config.sampling_rate = expected_sampling_rate;
    config.feat_config.feature_dim = setting->sherpa_ncnn_feature_dim;
    //初始化模型
    config.model_config.tokens = setting->sherpa_ncnn_tokens.toStdString();
    config.model_config.encoder_param = setting->sherpa_ncnn_encoder_param.toStdString();
    config.model_config.encoder_bin = setting->sherpa_ncnn_encoder_bin.toStdString();
    config.model_config.decoder_param = setting->sherpa_ncnn_decoder_param.toStdString();
    config.model_config.decoder_bin = setting->sherpa_ncnn_decoder_bin.toStdString();
    config.model_config.joiner_param = setting->sherpa_ncnn_joiner_param.toStdString();
    config.model_config.joiner_bin = setting->sherpa_ncnn_joiner_bin.toStdString();
    if (setting->sherpa_ncnn_num_threads > 0) {
        config.model_config.encoder_opt.num_threads = setting->sherpa_ncnn_num_threads;
        config.model_config.decoder_opt.num_threads = setting->sherpa_ncnn_num_threads;
        config.model_config.joiner_opt.num_threads = setting->sherpa_ncnn_num_threads;
    }
    if (setting->sherpa_ncnn_method != "greedy_search" && setting->sherpa_ncnn_method != "modified_beam_search") {
        qDebug() << "Invalid SHERPA_NCNN_METHOD" << setting->sherpa_ncnn_method;
        return false;
    }
    config.decoder_config.method = setting->sherpa_ncnn_method.toStdString();
    recognizer=std::make_unique<sherpa_ncnn::Recognizer>(config);
    stream=recognizer->CreateStream();
    return true;
}

QString ASRFrameText::BuildRecognizer(QByteArray & bytes)
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
  //  auto begin = std::chrono::steady_clock::now();
   // Q_UNUSED(begin);
    if (1) {
        stream->AcceptWaveform(16000, floatVector.data(),floatVector.size());
        // std::vector<float> tail_paddings(static_cast<int>(0.3 * expected_sampling_rate));  // 0.3 seconds at 16 kHz sample rate
        //  stream->AcceptWaveform(expected_sampling_rate, tail_paddings.data(),tail_paddings.size());
        stream->InputFinished();
        while (recognizer->IsReady(stream.get())) {
            recognizer->DecodeStream(stream.get());
        }
        bool is_endpoint = recognizer->IsEndpoint(stream.get());
        auto text = recognizer->GetResult(stream.get()).text;


        if (!text.empty() && last_text!=text) {
            last_text = text;
            std::transform(text.begin(), text.end(), text.begin(),
                           [](auto c) {
                               return std::tolower(c);
            });

        }
        if (is_endpoint) {
            emit finishRecognizer();
            if (!text.empty()) {
                (segment_index)++;
            }
            recognizer->Reset(stream.get());
        }
    }

    return  QString::fromStdString(last_text);
}





