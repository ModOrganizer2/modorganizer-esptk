#-------------------------------------------------
#
# Project created by QtCreator 2013-09-09T19:59:03
#
#-------------------------------------------------

QT       -= core gui

TARGET = esptk
TEMPLATE = lib
CONFIG += staticlib

SOURCES += espfile.cpp \
    record.cpp \
    subrecord.cpp

HEADERS += espfile.h \
    record.h \
    subrecord.h \
    esptypes.h \
		espexceptions.h
