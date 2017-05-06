#-------------------------------------------------
#
# Project created by QtCreator 2017-05-04T14:47:57
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WwMail
TEMPLATE = app


SOURCES += main.cpp\
        wwmail.cpp \
    accountmanager.cpp \
    addactdialog.cpp \
    imapthread.cpp

HEADERS  += wwmail.h \
    accountmanager.h \
    addactdialog.h \
    imapthread.h

FORMS    += wwmail.ui \
    accountmanager.ui \
    addactdialog.ui
