#-------------------------------------------------
#
# Project created by QtCreator 2014-01-27T23:02:09
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = emailip
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    smtp.cpp \
    setting.cpp \
    checkandemail.cpp

HEADERS  += mainwindow.h \
    smtp.h \
    setting.h \
    checkandemail.h

FORMS    += mainwindow.ui
