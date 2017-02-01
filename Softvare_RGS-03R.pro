#-------------------------------------------------
#
# Project created by QtCreator 2016-10-16T19:18:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Softvare_RGS-03R
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h
HEADERS += ftd2xx.h

win32:OBJECTS_DIR = build/o/win32
win32:LIBS += ftd2xx.lib -lsetupapi -lws2_32
win32:HEADERS += ftd2xx.h
win32:MOC_DIR = build/moc_win32

unix:OBJECTS_DIR = build/o/unix
# unix:LIBS += /usr/lib/x86_64-linux-gnu/libftdi.so
#unix:HEADERS += /usr/include/*
unix:MOC_DIR = build/moc_unix
DEFINES += BN_NO_DEBUG

FORMS    += mainwindow.ui

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../usr/local/lib/release/ -lftd2xx
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../usr/local/lib/debug/ -lftd2xx
#else:unix: LIBS += -L$$PWD/../../../usr/local/lib/ -lftd2xx

#INCLUDEPATH += $$PWD/../../../usr/local/include
#DEPENDPATH += $$PWD/../../../usr/local/include


#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../usr/local/lib/release/ -lftd2xx
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../usr/local/lib/debug/ -lftd2xx
#else:unix: LIBS += -L$$PWD/../../../usr/local/lib/ -lftd2xx

#INCLUDEPATH += $$PWD/../../../usr/local/include
#DEPENDPATH += $$PWD/../../../usr/local/include

#win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../usr/local/lib/release/libftd2xx.a
#else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../usr/local/lib/debug/libftd2xx.a
#else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../usr/local/lib/release/ftd2xx.lib
#else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../usr/local/lib/debug/ftd2xx.lib
#else:unix: PRE_TARGETDEPS += $$PWD/../../../usr/local/lib/libftd2xx.a
