#-------------------------------------------------
#
# Project created by QtCreator 2022-05-23T20:45:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = betikyukleyici
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    appwidget.cpp \
    kategoriwidget.cpp \
        mainwindow.cpp \
    main.cpp

HEADERS += \
    appwidget.h \
    function.h \
    kategoriwidget.h \
        mainwindow.h \
    filecrud.h \
    hakkinda.h \
    process.h

FORMS +=

target.path = /usr/bin

desktop_file.files = betikyukleyici.desktop
desktop_file.path = /usr/share/applications/

icon.files = icons/betikyukleyici.svg
icon.path = /usr/share/betikyukleyici


INSTALLS += target desktop_file icon
DISTFILES += \
       betikyukleyici.desktop\
          icons/remove.svg

RESOURCES += \
    resource.qrc
