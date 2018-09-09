#-------------------------------------------------
#
# Project created by QtCreator 2018-09-07T14:44:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WorkHelper
TEMPLATE = app


SOURCES += main.cpp\
    Modules/ImageExInfos/simageexinfos.cpp \
    Modules/FileNameFactor/sfilenamefactor.cpp \
    Modules/MainUi/smainwidget.cpp \
    Component/SDragListWidget.cpp \
    Component/SImageView.cpp \
    Modules/FilesReplace/sfilesreplace.cpp \
    Component/SDragMoveListWidget.cpp


HEADERS  += \
    Modules/ImageExInfos/simageexinfos.h \
    Modules/FileNameFactor/sfilenamefactor.h \
    Modules/MainUi/smainwidget.h \
    Component/SDragListWidget.h \
    Modules/uimodules.h \
    Component/SImageView.h \
    Modules/FilesReplace/sfilesreplace.h \
    Component/SDragMoveListWidget.h


FORMS    += \
    Modules/ImageExInfos/simageexinfos.ui \
    Modules/FileNameFactor/sfilenamefactor.ui \
    Modules/MainUi/smainwidget.ui \
    Modules/FilesReplace/sfilesreplace.ui

