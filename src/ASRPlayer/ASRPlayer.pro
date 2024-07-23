TEMPLATE = lib
CONFIG += staticlib
QT       += core gui multimedia opengl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

linux-g++* {
    CONFIG(debug, debug|release){
        message(Debug build)
        TARGET = ASRPlayer
        INCLUDEPATH +=$$PWD/../Vendor/sherpa-onnx
        INCLUDEPATH +=$$PWD/../Vendor/sherpa-onnx/build/_deps/kaldi_decoder-src
        INCLUDEPATH +=$$PWD/../Vendor/sherpa-onnx/build/_deps/openfst-src/src/include
        INCLUDEPATH +=$$PWD/../Vendor/sherpa-onnx/build/_deps/kaldifst-src
        INCLUDEPATH +=$$PWD/../Vendor/sherpa-onnx/build/_deps/onnxruntime-src/include
        INCLUDEPATH +=$$PWD/../Vendor/sherpa-ncnn
        INCLUDEPATH +=$$PWD/../Vendor/sherpa-ncnn/build/_deps/ncnn-src/src
        INCLUDEPATH +=$$PWD/../Vendor/sherpa-ncnn/build/_deps/ncnn-build/src

        LIBS += -L$$PWD/../lib/Linux -lCore
        LIBS += -L$$PWD/../lib/Linux -lFFmpegPlayer
        LIBS += -L$$PWD/../lib/Linux -lASRPlayer
        LIBS  += -Wall -lpthread  -lgomp -lcblas
        LIBS += -L$$PWD/lib/Linux -lCore
        DESTDIR = $$PWD/lib/Linux
        #DEPENDPATH += $$PWD/dll
        release

    }

    CONFIG(release, debug|release){
        message(Release build)
        TARGET = ASRPlayer
        INCLUDEPATH +=$$PWD/../Vendor/sherpa-onnx
        INCLUDEPATH +=$$PWD/../Vendor/sherpa-onnx/build/_deps/kaldi_decoder-src
        INCLUDEPATH +=$$PWD/../Vendor/sherpa-onnx/build/_deps/openfst-src/src/include
        INCLUDEPATH +=$$PWD/../Vendor/sherpa-onnx/build/_deps/kaldifst-src
        INCLUDEPATH +=$$PWD/../Vendor/sherpa-onnx/build/_deps/onnxruntime-src/include
        INCLUDEPATH +=$$PWD/../Vendor/sherpa-ncnn
        INCLUDEPATH +=$$PWD/../Vendor/sherpa-ncnn/build/_deps/ncnn-src/src
        INCLUDEPATH +=$$PWD/../Vendor/sherpa-ncnn/build/_deps/ncnn-build/src


        LIBS  += -Wall -lpthread  -lgomp -lcblas
        #DESTDIR = $$PWD/lib/Linux
        #LIBS += -L$$PWD/lib/Linux -lLive2DCubismCore
    }
    #DEFINES += CSM_TARGET_LINUX_GL
    LIBS += -Wall -lpthread  -lgomp -lcblas
}

win32-msvc*{
    CONFIG(debug, debug|release){
        message(Debug build)
        TARGET = FFmpegPlayer
        #DESTDIR = $$PWD/lib/Win32
        #LIBS += -L$$PWD/lib/Win32 -lLive2DCubismCore_MDd
        release
    }

    CONFIG(release, debug|release){
        message(Release build)
        TARGET = FFmpegPlayer
        #DESTDIR = $$PWD/lib/Win32
        #LIBS += -L$$PWD/lib/Win32 -lLive2DCubismCore_MD
    }

    DEFINES += WIN32
    DEFINES += _WINDOWS
    DEFINES += CSM_TARGET_WIN_GL
}




# $$VENDOR_DIRS/build/_deps/kaldi_decoder-src/kaldi-decoder/csrc/decodable-ctc.cc \
#  #$$VENDOR_DIRS/build/_deps/kaldi_decoder-src/kaldi-decoder/csrc/eigen-test.cc \
# $$VENDOR_DIRS/build/_deps/kaldi_decoder-src/kaldi-decoder/csrc/eigen.cc \
# $$VENDOR_DIRS/build/_deps/kaldi_decoder-src/kaldi-decoder/csrc/faster-decoder.cc \
#  #$$VENDOR_DIRS/build/_deps/kaldi_decoder-src/kaldi-decoder/csrc/hash-list-test.cc \
# $$VENDOR_DIRS/build/_deps/kaldi_decoder-src/kaldi-decoder/csrc/lattice-faster-decoder.cc \
# $$VENDOR_DIRS/build/_deps/kaldi_decoder-src/kaldi-decoder/csrc/lattice-simple-decoder.cc \
# $$VENDOR_DIRS/build/_deps/kaldi_decoder-src/kaldi-decoder/csrc/simple-decoder.cc \
# $$VENDOR_DIRS/build/_deps/kaldi_native_fbank-src/kaldi-native-fbank/csrc/feature-fbank.cc \
# $$VENDOR_DIRS/build/_deps/kaldi_native_fbank-src/kaldi-native-fbank/csrc/feature-functions.cc \
# $$VENDOR_DIRS/build/_deps/kaldi_native_fbank-src/kaldi-native-fbank/csrc/feature-mfcc.cc \
# $$VENDOR_DIRS/build/_deps/kaldi_native_fbank-src/kaldi-native-fbank/csrc/feature-window.cc \
# $$VENDOR_DIRS/build/_deps/kaldi_native_fbank-src/kaldi-native-fbank/csrc/fftsg.cc \
# $$VENDOR_DIRS/build/_deps/kaldi_native_fbank-src/kaldi-native-fbank/csrc/kaldi-math.cc \
# $$VENDOR_DIRS/build/_deps/kaldi_native_fbank-src/kaldi-native-fbank/csrc/log.cc \
# $$VENDOR_DIRS/build/_deps/kaldi_native_fbank-src/kaldi-native-fbank/csrc/mel-computations.cc \
# $$VENDOR_DIRS/build/_deps/kaldi_native_fbank-src/kaldi-native-fbank/csrc/online-feature.cc \
# $$VENDOR_DIRS/build/_deps/kaldi_native_fbank-src/kaldi-native-fbank/csrc/rfft.cc \
#  #$$VENDOR_DIRS/build/_deps/kaldi_native_fbank-src/kaldi-native-fbank/csrc/test-log.cc \
#  #$$VENDOR_DIRS/build/_deps/kaldi_native_fbank-src/kaldi-native-fbank/csrc/test-online-fbank.cc \
#  #$$VENDOR_DIRS/build/_deps/kaldi_native_fbank-src/kaldi-native-fbank/csrc/test-online-feature.cc \
#  #$$VENDOR_DIRS/build/_deps/kaldi_native_fbank-src/kaldi-native-fbank/csrc/test-rfft.cc \
# $$VENDOR_DIRS/build/_deps/kaldi_native_fbank-src/kaldi-native-fbank/csrc/whisper-feature.cc \
# $$VENDOR_DIRS/build/_deps/simple-sentencepiece-src/ssentencepiece/csrc/ssentencepiece.cc \
#  #$$VENDOR_DIRS/build/_deps/simple-sentencepiece-src/ssentencepiece/csrc/ssentencepiece_test.cc



HEADERS += \
    $$PWD/ASRFrameName.h \
    $$PWD/ASRFrameText.h \
    $$PWD/ASRMicrophone.h \
    $$PWD/ASRSettings.h \
    $$PWD/ASRSpeaker.h \
    $$PWD/ASRThreader.h \
    $$PWD/QASRPlayer.h \
    $$PWD/QThreader.h


SOURCES += \
    $$PWD/ASRFrameName.cpp \
    $$PWD/ASRFrameText.cpp \
    $$PWD/ASRMicrophone.cpp \
    $$PWD/ASRSpeaker.cpp \
    $$PWD/ASRThreader.cpp \
    $$PWD/QThreader.cpp \
    $$PWD/ASRSettings.cpp
