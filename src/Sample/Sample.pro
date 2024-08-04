QT       += core gui opengl widgets multimedia

# In Qt6 to use QOpenglWidget, we need add QT += openglwidgets.
greaterThan(QT_MAJOR_VERSION, 5){
    message(Building with Qt6 or Higher)
    QT += openglwidgets
}


CONFIG += c++17
TARGET = Sample

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/../SherpaOnnxPlayer
INCLUDEPATH += $$PWD/../SherpaNcnnPlayer
INCLUDEPATH += $$PWD/../FFmpegPlayer
INCLUDEPATH += $$PWD/../Bootstrap

CONFIG += debug_and_release


linux-g++* {
    message(Compling with linux-g++)
    CONFIG(debug, debug|release){
        message(Debug build)
        #语音呼唤
        INCLUDEPATH +=$$PWD/../components/sherpa-onnx/include
        INCLUDEPATH +=$$PWD/../components/sherpa-onnx/include/kaldi_decoder-src
        INCLUDEPATH +=$$PWD/../components/sherpa-onnx/include/openfst-src/src/include
        INCLUDEPATH +=$$PWD/../components/sherpa-onnx/include/kaldifst-src
        INCLUDEPATH +=$$PWD/../components/sherpa-onnx/include/onnxruntime-src/include
        #语音识别
        INCLUDEPATH +=$$PWD/../components/sherpa-ncnn/include
        INCLUDEPATH +=$$PWD/../components/sherpa-ncnn/include/ncnn-src/src
        INCLUDEPATH +=$$PWD/../components/sherpa-ncnn/include/ncnn-build/src

        LIBS += -L$$PWD/../lib/Linux -lSherpaNcnnPlayer
        LIBS += -L$$PWD/../lib/Linux -lSherpaOnnxPlayer
        LIBS += -L$$PWD/../lib/Linux -lFFmpegPlayer
        LIBS += -L$$PWD/../lib/Linux -lBootstrap

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
        #libkaldi-native-fbank-core.a  libsherpa-ncnn-core.a
        #libncnn.a                     libsherpa-ncnn-portaudio_static.a
        #libsherpa-ncnn-c-api.a
        LIBS += -L$$PWD/../components/sherpa-ncnn/lib/Linux -lkaldi-native-fbank-core
        LIBS += -L$$PWD/../components/sherpa-ncnn/lib/Linux -lsherpa-ncnn-core
        LIBS += -L$$PWD/../components/sherpa-ncnn/lib/Linux -lncnn
        LIBS += -L$$PWD/../components/sherpa-ncnn/lib/Linux -lsherpa-ncnn-portaudio_static
        LIBS += -L$$PWD/../components/sherpa-ncnn/lib/Linux -lsherpa-ncnn-c-api

        INCLUDEPATH +=$$PWD/../components/sherpa-onnx/include/kaldi_native_fbank-src
        INCLUDEPATH +=$$PWD/../components/sherpa-onnx/include/simple-sentencepiece-src
        SOURCES +=$$PWD/../components/sherpa-onnx/src/sherpa-onnx/csrc/utils.cc
        SOURCES +=$$PWD/../components/sherpa-onnx/src/sherpa-onnx/csrc/online-stream.cc
        SOURCES +=$$PWD/../components/sherpa-onnx/src/sherpa-onnx/csrc/features.cc

        #LIBS += -L$$PWD/../lib/Linux -lLive2DCubismCore

        DEPENDPATH += $$PWD/../dll
        release

    }
    CONFIG(release, debug|release){
        message(Release build)

    }

    DEFINES += CSM_TARGET_LINUX_GL
    LIBS += -lavcodec
    LIBS += -lavdevice
    LIBS += -lavfilter
    LIBS += -lavformat
    LIBS += -lavutil
    LIBS += -lswscale
    LIBS += -lswresample
    LIBS += -lcblas
    LIBS += -lopencv_core
    LIBS += -lopencv_highgui
    LIBS += -lopencv_imgcodecs
    LIBS += -lopencv_imgproc
    LIBS += -lopencv_videoio
    LIBS += -Wall -lpthread
    LIBS  += -Wall -lpthread  -lgomp -lcblas
}

win32-msvc*{
    message(Compling with win32-msvc)
    CONFIG(debug, debug|release){
        message(Debug build)
        #LIBS += -L$$PWD/../lib/Win32 -lLive2DCubismCore_MDd
        #LIBS += -L$$PWD/../lib/Win32 -lFrameworkd

    }

    CONFIG(release, debug|release){
        message(Release build)
        #LIBS += -L$$PWD/../lib/Win32 -lLive2DCubismCore_MD
        #LIBS += -L$$PWD/../lib/Win32 -lFramework

    }

    DEFINES += WIN32
    DEFINES += _WINDOWS
    DEFINES += CSM_TARGET_WIN_GL

    #LIBS += -lOpenGL32
    #LIBS += -lUser32
    #LIBS += -lGlu32
}

win32-g++*{
    error(Please use MSVC on Win32)
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# CONFIG += file_copies

# resources.files = $$PWD/Resources
# resources.path = $$OUT_PWD

COPIES += resources

DISTFILES += \
    ChatPlayer_zh_CN.ts \
    README.md

HEADERS += \
    ASRFramePlayer.h \
    ASRFrameThreader.h \
    CameraPlayer.h \
    GamePlayer.h \
    MaskPlayer.h \
    UserWidget.h

SOURCES += \
    ASRFramePlayer.cpp \
    ASRFrameThreader.cpp \
    CameraPlayer.cpp \
    GamePlayer.cpp \
    MaskPlayer.cpp \
    UserWidget.cpp \
    main.cpp

RESOURCES += \
    ../images/images.qrc
