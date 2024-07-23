TEMPLATE = lib
CONFIG += staticlib

QT       += core gui multimedia opengl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

linux-g++* {
    CONFIG(debug, debug|release){
        message(Debug build)
        TARGET = NaturalPlayer
        DESTDIR = $$PWD/../lib/Linux
        #LIBS += -L$$PWD/../lib/Linux -lLive2DCubismCore
        #DEPENDPATH += $$PWD/../dll
        release

    }

    CONFIG(release, debug|release){
        message(Release build)
        TARGET = NaturalPlayer
        DESTDIR = $$PWD/../lib/Linux
        #LIBS += -L$$PWD/../lib/Linux -lLive2DCubismCore

    }
    #DEFINES += CSM_TARGET_LINUX_GL

}

win32-msvc*{
    CONFIG(debug, debug|release){
        message(Debug build)
        TARGET = NaturalPlayer
        release

    }

    CONFIG(release, debug|release){
        message(Release build)
        TARGET = NaturalPlayer
    }

    DEFINES += WIN32
    DEFINES += _WINDOWS
    DEFINES += CSM_TARGET_WIN_GL
}

win32-g++*{
    error(Please use MSVC on Win32)
}

HEADERS += \
    BaseSpeaker.h \
    BaseThreader.h \
    CameraManager.h \
    QSettingEnergies.h \
    SoundThreader.h

SOURCES += \
    BaseSpeaker.cpp \
    BaseThreader.cpp \
    CameraManager.cpp \
    QSettingEnergies.cpp \
    SoundThreader.cpp

