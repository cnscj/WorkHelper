#-------------------------------------------------
#
# Project created by QtCreator 2018-09-07T14:44:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WorkHelper
TEMPLATE = app


SOURCES  += \
    Component/UI/SDragListWidget.cpp \
    Component/UI/SDragMoveListWidget.cpp \
    Component/UI/SImageDrawWidget.cpp \
    Component/UI/SImageView.cpp \
    Modules/CoordinateMeasure/scoordinatemeasure.cpp \
    Modules/FileNameFactor/sfilenamefactor.cpp \
    Modules/FilesReplace/sfilesreplace.cpp \
    Modules/ImageExInfos/simageexinfos.cpp \
    Modules/MainUi/smainwidget.cpp \
    Base/SMarkPoint.cpp \
    main.cpp \
    Component/SDrawTool.cpp

HEADERS  += \
    Component/UI/SDragListWidget.h \
    Component/UI/SDragMoveListWidget.h \
    Component/UI/SImageDrawWidget.h \
    Component/UI/SImageView.h \
    Modules/CoordinateMeasure/scoordinatemeasure.h \
    Modules/FileNameFactor/sfilenamefactor.h \
    Modules/FilesReplace/sfilesreplace.h \
    Modules/ImageExInfos/simageexinfos.h \
    Modules/MainUi/smainwidget.h \
    Modules/uimodules.h \
    Base/SMarkPoint.h \
    Component/SDrawTool.h

FORMS    += \
    Modules/ImageExInfos/simageexinfos.ui \
    Modules/FileNameFactor/sfilenamefactor.ui \
    Modules/MainUi/smainwidget.ui \
    Modules/FilesReplace/sfilesreplace.ui \
    Modules/CoordinateMeasure/scoordinatemeasure.ui

