#-------------------------------------------------
#
# Project created by QtCreator 2014-12-22T10:52:53
#
#-------------------------------------------------

QT       += core gui
#CONFIG   += c++14
QMAKE_CXXFLAGS += -Wextra -Wall -pedantic -Wconversion -std=c++1z

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AnimalsEditor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    animalswindow.cpp \
    animal.cpp \
    type.cpp \
    typeswindow.cpp \
    database.cpp \
    moveswindow.cpp \
    move.cpp \
    data.cpp \
    datawindow.cpp \
    comboboxdelegate.cpp \
    animalmoveswindow.cpp \
    animaldatabase.cpp \
	movedatabase.cpp# \
	#tdatabase.tpp

HEADERS  += mainwindow.h \
    animalswindow.h \
    animal.h \
    type.h \
    typeswindow.h \
    database.h \
    moveswindow.h \
    move.h \
    data.h \
    datawindow.h \
    comboboxdelegate.h \
    numericmodel.h \
    animalmoveswindow.h \
    animaldatabase.h \
    movedatabase.h \
    tdatabase.hpp

FORMS    += mainwindow.ui \
    animalswindow.ui \
    typeswindow.ui \
    moveswindow.ui \
    animalmoveswindow.ui
