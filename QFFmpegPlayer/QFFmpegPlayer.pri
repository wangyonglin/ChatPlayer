contains(DEFINES, unix)
{
    INCLUDEPATH +=\
        $$PWD/include

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

