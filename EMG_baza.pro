#-------------------------------------------------
#
# Project created by QtCreator 2017-11-25T18:42:18
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EMG_baza
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    qcustomplot.cpp \
    dane.cpp \
    mmg.cpp \
    emg.cpp \
    navi.cpp \
    sensglove.cpp \
    forcesensor.cpp

HEADERS += \
        mainwindow.h \
    qcustomplot.h \
    dane.h \
    mmg.h \
    emg.h \
    navi.h \
    sensglove.h \
    forcesensor.h

FORMS += \
    mainwindow.ui
