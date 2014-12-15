#-------------------------------------------------
#
# Project created by QtCreator 2014-12-09T11:20:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Threads4
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    buffershared.cpp \
    threadconsumer.cpp \
    threadproducer.cpp

HEADERS  += mainwindow.h \
    buffershared.h \
    threadconsumer.h \
    threadproducer.h

FORMS    += mainwindow.ui
