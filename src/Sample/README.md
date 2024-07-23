# ChatPlayer

#### SherpaOnnxPlayer.pro
```
INCLUDEPATH +=$$PWD/../components/sherpa-onnx/include
INCLUDEPATH +=$$PWD/../components/sherpa-onnx/include/kaldi_decoder-src
INCLUDEPATH +=$$PWD/../components/sherpa-onnx/include/openfst-src/src/include
INCLUDEPATH +=$$PWD/../components/sherpa-onnx/include/kaldifst-src
INCLUDEPATH +=$$PWD/../components/sherpa-onnx/include/onnxruntime-src/include

LIBS += -L$$PWD/../components/sherpa-onnx/lib/Linux -lonnxruntime
LIBS += -L$$PWD/../components/sherpa-onnx/lib/Linux -lcargs
LIBS += -L$$PWD/../components/sherpa-onnx/lib/Linux -lsherpa-onnx-fst
LIBS += -L$$PWD/../components/sherpa-onnx/lib/Linux -lespeak-ng
LIBS += -L$$PWD/../components/sherpa-onnx/lib/Linux -lsherpa-onnx-fstfar
LIBS += -L$$PWD/../components/sherpa-onnx/lib/Linux -lkaldi-decoder-core
LIBS += -L$$PWD/../components/sherpa-onnx/lib/Linux -lsherpa-onnx-kaldifst-core
LIBS += -L$$PWD/../components/sherpa-onnx/lib/Linux -lkaldi-native-fbank-core
LIBS += -L$$PWD/../components/sherpa-onnx/lib/Linux -lsherpa-onnx-portaudio_static
LIBS += -L$$PWD/../components/sherpa-onnx/lib/Linux -lpiper_phonemize
LIBS += -L$$PWD/../components/sherpa-onnx/lib/Linux -lssentencepiece_core
LIBS += -L$$PWD/../components/sherpa-onnx/lib/Linux -lsherpa-onnx-c-api
LIBS += -L$$PWD/../components/sherpa-onnx/lib/Linux -lucd
LIBS += -L$$PWD/../components/sherpa-onnx/lib/Linux -lsherpa-onnx-core

INCLUDEPATH +=$$PWD/../components/sherpa-onnx/include/kaldi_native_fbank-src
INCLUDEPATH +=$$PWD/../components/sherpa-onnx/include/simple-sentencepiece-src
SOURCES +=$$PWD/../components/sherpa-onnx/src/sherpa-onnx/csrc/utils.cc
SOURCES +=$$PWD/../components/sherpa-onnx/src/sherpa-onnx/csrc/online-stream.cc
SOURCES +=$$PWD/../components/sherpa-onnx/src/sherpa-onnx/csrc/features.cc
```
