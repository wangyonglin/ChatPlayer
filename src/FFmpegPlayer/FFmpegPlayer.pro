TEMPLATE = lib
CONFIG += staticlib
QT       += core gui multimedia opengl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets



linux-g++* {
    CONFIG(debug, debug|release){
        message(Debug build)
        TARGET = FFmpegPlayer
        DESTDIR = $$PWD/../lib/Linux
        #LIBS += -L$$PWD/../lib/Linux -lLive2DCubismCore
        #DEPENDPATH += $$PWD/../dll
        release

    }

    CONFIG(release, debug|release){
        message(Release build)
        TARGET = FFmpegPlayer
        DESTDIR = $$PWD/../lib/Linux
        #LIBS += -L$$PWD/../lib/Linux -lLive2DCubismCore

    }
    #DEFINES += CSM_TARGET_LINUX_GL
    LIBS += -lavcodec
    LIBS += -lavdevice
    LIBS += -lavfilter
    LIBS += -lavformat
    LIBS += -lavutil
    LIBS += -lswscale
    LIBS += -lswresample
    LIBS += -lcblas
    LIBS += -Wall -lpthread
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
    $$PWD/QFFmpegAudioDecoder.h \
    $$PWD/QFFmpegDemuxer.h \
    $$PWD/QFFmpegFrame.h \
    $$PWD/QFFmpegManager.h \
    $$PWD/QFFmpegPacket.h \
    $$PWD/QFFmpegPlayer.h \
    $$PWD/QFFmpegRender.h \
    $$PWD/QFFmpegResampler.h \
    $$PWD/QFFmpegSynchronizer.h \
    $$PWD/QFFmpegThreader.h \
    $$PWD/QFFmpegVideoDecoder.h

SOURCES += \
    $$PWD/QFFmpegAudioDecoder.cpp \
    $$PWD/QFFmpegDemuxer.cpp \
    $$PWD/QFFmpegFrame.cpp \
    $$PWD/QFFmpegManager.cpp \
    $$PWD/QFFmpegPacket.cpp \
    $$PWD/QFFmpegPlayer.cpp \
    $$PWD/QFFmpegRender.cpp \
    $$PWD/QFFmpegResampler.cpp \
    $$PWD/QFFmpegSynchronizer.cpp \
    $$PWD/QFFmpegThreader.cpp \
    $$PWD/QFFmpegVideoDecoder.cpp

