QT += core gui widgets

CONFIG += c++11

TARGET = apktool
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

DESTDIR = ../bin

RESOURCES += \
    res.qrc \
    icon.qrc

win32 {
   RC_FILE = res/main.rc
}

CONFIG += resources_big

