#-------------------------------------------------
#
# Project created by QtCreator 2015-04-22T21:59:10
#
#-------------------------------------------------

QT       += core gui
QT       += multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = myproject
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    login.cpp \
    entry.cpp \
    user.cpp \
    lrc.cpp

HEADERS  += mainwindow.h \
    login.h \
    entry.h \
    list.h \
    user.h \
    lrc.h

FORMS    += mainwindow.ui \
    login.ui \
    entry.ui \
    user.ui \
    lrc.ui

RESOURCES += \
    res.qrc
