TEMPLATE = lib
CONFIG += staticlib
QT       += core gui multimedia opengl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += $$PWD/../NaturalPlayer

linux-g++* {
    CONFIG(debug, debug|release){
        message(Debug build)
        TARGET = SherpaOnnxPlayer
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

        DESTDIR = $$PWD/../lib/Linux
        LIBS += -L$$PWD/../lib/Linux -lLive2DCubismCore
        #DEPENDPATH += $$PWD/../dll
        release

    }

    CONFIG(release, debug|release){
        message(Release build)
        TARGET = SherpaOnnxPlayer
        INCLUDEPATH +=$$PWD/../components/sherpa-onnx/include
        INCLUDEPATH +=$$PWD/../components/sherpa-onnx/include/kaldi_decoder-src
        INCLUDEPATH +=$$PWD/../components/sherpa-onnx/include/openfst-src/src/include
        INCLUDEPATH +=$$PWD/../components/sherpa-onnx/include/kaldifst-src
        INCLUDEPATH +=$$PWD/../components/sherpa-onnx/include/onnxruntime-src/include
        DESTDIR = $$PWD/../lib/Linux
        #LIBS += -L$$PWD/../lib/Linux -lLive2DCubismCore

    }
    #DEFINES += CSM_TARGET_LINUX_GL
}

win32-msvc*{
    CONFIG(debug, debug|release){
        message(Debug build)
        TARGET = FFmpegPlayer
        #DESTDIR = $$PWD/../lib/Win32
        #LIBS += -L$$PWD/../lib/Win32 -lLive2DCubismCore_MDd
        release

    }

    CONFIG(release, debug|release){
        message(Release build)
        TARGET = FFmpegPlayer
        #DESTDIR = $$PWD/../lib/Win32
        #LIBS += -L$$PWD/../lib/Win32 -lLive2DCubismCore_MD
    }

    DEFINES += WIN32
    DEFINES += _WINDOWS
    DEFINES += CSM_TARGET_WIN_GL
}

win32-g++*{
    error(Please use MSVC on Win32)
}

HEADERS += \
    SherpaOnnxPlayer.h \
    SherpaOnnxQSettings.h

SOURCES += \
    SherpaOnnxPlayer.cpp \
    SherpaOnnxQSettings.cpp
