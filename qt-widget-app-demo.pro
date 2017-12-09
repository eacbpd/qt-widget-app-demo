#-------------------------------------------------
#
# Project created by QtCreator 2017-11-30T00:51:52
#
#-------------------------------------------------

QT       += core gui\
            network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt-widget-app-demo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    treewidget.cpp \
    listwidget.cpp \
    tablewidget.cpp \
    mylistdelegate.cpp \
    tabwidget.cpp \
    stackedwidget.cpp \
    notepad.cpp \
    painter.cpp \
    network.cpp \
    seekbar.cpp



HEADERS  += mainwindow.h \
    treewidget.h \
    listwidget.h \
    tablewidget.h \
    mylistdelegate.h \
    tabwidget.h \
    stackedwidget.h \
    notepad.h \
    painter.h \
    network.h \
    seekbar.h



FORMS    += mainwindow.ui \
    treewidget.ui \
    listwidget.ui \
    tablewidget.ui \
    tabwidget.ui \
    stackedwidget.ui \
    notepad.ui \
    painter.ui \
    network.ui \
    seekbar.ui


RESOURCES += \
    resource.qrc \
    player_res.qrc
