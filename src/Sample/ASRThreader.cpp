


// ASRThreader::ASRThreader(QObject *parent)
//     : BaseThreader{parent},
//     asrMicrophone(new ASRMicrophone(parent)),
//     asrFrameName(new ASRFrameName(parent)),
//     asrSpeaker(new ASRSpeaker(parent)),
//     asrFrameText(new ASRFrameText(parent))

// {
//     connect(asrFrameName,&ASRFrameName::finishRecognizer,[=](qint32 id,const QString & name){
//         bRecognizer=true;
//         qDebug()  <<"识别为：" <<name;

//     });


//     connect(asrFrameText,&ASRFrameText::finishRecognizer,[=](){

//         bRecognizer=false;
//         listText.clear();
//         qDebug() << "识别结束";
//         emit finishRecognizer();
//     });
// }

// void ASRThreader::InitThreader(ASRSettings *setting)
// {
//     this->setting=setting;
//     asrMicrophone->InitMicrophone(setting);
//     asrFrameName->InitRecognizer(setting);
//     asrFrameText->InitRecognizer(setting);
//     asrSpeaker->InitSpeaker(setting);
// }

// void ASRThreader::loopStart(QThreader::Priority pri)
// {
//     QThreader::loopStart(pri);
// }

// void ASRThreader::loopStop()
// {
//     QThreader::loopStop();
// }

// void ASRThreader::loopRunnable()
// {
//     QByteArray bytes= asrMicrophone->ReadAll();
//     if(setting->sherpa_onnx_start==ASRSettings::on){
//         asrFrameName->BuildRecognizer(bytes);
//         if(bRecognizer==true){
//             QString buffer = asrFrameText->BuildRecognizer(bytes);
//             if(!buffer.isEmpty()){
//                 if(listText.size()>0){
//                     listText.clear();
//                 }
//                 listText.append(buffer);
//                 emit updateRecognizer();
//             }
//         }
//     }
//     if(setting->asr_speaker_play==ASRSettings::on){
//         asrSpeaker->PlaySpeaker(bytes);
//     }
// }







