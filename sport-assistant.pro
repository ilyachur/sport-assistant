#-------------------------------------------------
#
# Project created by QtCreator 2015-07-03T12:46:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sport-assistant
TEMPLATE = app


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/fit/fit.c \
    src/fit/fit_convert.c \
    src/fit/fit_crc.c \
    src/fit/fit_example.c \
    src/fit/fit_product.c \
    src/fit/fit_ram.c

HEADERS  += src/mainwindow.h \
    src/fit/fit.h \
    src/fit/fit_config.h \
    src/fit/fit_convert.h \
    src/fit/fit_crc.h \
    src/fit/fit_example.h \
    src/fit/fit_include.h \
    src/fit/fit_product.h \
    src/fit/fit_ram.h

FORMS    += forms/mainwindow.ui
