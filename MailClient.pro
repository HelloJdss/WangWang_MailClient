#-------------------------------------------------
#
# Project created by QtCreator 2017-04-08T20:06:33
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MailClient
TEMPLATE = app



SOURCES += main.cpp\
        clientwindow.cpp \
    dialog_login.cpp \
    stdafx.cpp \
    imap.cpp \
    smtp.cpp

HEADERS  += clientwindow.h \
    dialog_login.h \
    stdafx.h \
    imap.h \
    smtp.h

FORMS    += clientwindow.ui \
    dialog_login.ui

CONFIG+=precompile_header
PRECOMPILED_HEADER=stdafx.h
