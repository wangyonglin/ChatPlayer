TEMPLATE = lib
CONFIG += staticlib
QT       += core gui multimedia opengl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += $$PWD/../NaturalPlayer

linux-g++* {
    CONFIG(debug, debug|release){
        message(Debug build)
        TARGET = SherpaNcnnPlayer
        INCLUDEPATH +=$$PWD/../components/sherpa-ncnn/include
        INCLUDEPATH +=$$PWD/../components/sherpa-ncnn/include/ncnn-src/src
        INCLUDEPATH +=$$PWD/../components/sherpa-ncnn/include/ncnn-build/src

        #LIBS += -L$$PWD/../components/sherpa-onnx/lib/Linux -lonnxruntime


        #INCLUDEPATH +=$$PWD/../components/sherpa-onnx/include/kaldi_native_fbank-src

        #SOURCES +=$$PWD/../components/sherpa-onnx/src/sherpa-onnx/csrc/utils.cc


        DESTDIR = $$PWD/../lib/Linux
        LIBS += -L$$PWD/../lib/Linux -lLive2DCubismCore
        #DEPENDPATH += $$PWD/../dll
        release

    }

    CONFIG(release, debug|release){
        message(Release build)
        TARGET = SherpaOnnxPlayer
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
    SherpaNcnnPlayer.h \
    SherpaNcnnQSettings.h

SOURCES += \
    SherpaNcnnPlayer.cpp \
    SherpaNcnnQSettings.cpp

