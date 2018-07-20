#-------------------------------------------------
#
# Project created by QtCreator 2018-07-20T17:22:15
#
#-------------------------------------------------

QT       += core gui
QT += webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = baiduMap
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    rewritebaidumaphtml.h

FORMS    += mainwindow.ui
