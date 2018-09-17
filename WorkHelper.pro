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
    Component/UI/SImageDrawWidget.cpp \
    Modules/CoordinateMeasure/scoordinatemeasure.cpp \
    Modules/FileNameFactor/sfilenamefactor.cpp \
    Modules/FilesReplace/sfilesreplace.cpp \
    Modules/ImageExInfos/simageexinfos.cpp \
    Modules/MainUi/smainwidget.cpp \
    Base/SMarkPoint.cpp \
    main.cpp \
    Component/SDrawTool.cpp \
    Modules/FilesReplace/sdragkeylistwidget.cpp \
    Modules/FilesReplace/sdragsortlistwidget.cpp \
    Modules/ImageExInfos/simagedrawexinfowidget.cpp \
    Component/UI/SPointWidget.cpp \
    Component/UI/SImageWidget.cpp \
    Util/SWidgetUtil.cpp \
    Util/SPaintUtil.cpp \
    Modules/CoordinateMeasure/sscrollareacontentwidget.cpp \
    Component/UI/SPictureBox.cpp

HEADERS  += \
    Component/UI/SDragListWidget.h \
    Component/UI/SImageDrawWidget.h \
    Modules/CoordinateMeasure/scoordinatemeasure.h \
    Modules/FileNameFactor/sfilenamefactor.h \
    Modules/FilesReplace/sfilesreplace.h \
    Modules/ImageExInfos/simageexinfos.h \
    Modules/MainUi/smainwidget.h \
    Modules/uimodules.h \
    Base/SMarkPoint.h \
    Component/SDrawTool.h \
    Modules/FilesReplace/sdragkeylistwidget.h \
    Modules/FilesReplace/sdragsortlistwidget.h \
    Modules/ImageExInfos/simagedrawexinfowidget.h \
    Component/UI/SPointWidget.h \
    Component/UI/SImageWidget.h \
    Util/SWidgetUtil.h \
    Util/SPaintUtil.h \
    Modules/CoordinateMeasure/sscrollareacontentwidget.h \
    Component/UI/SPictureBox.h \
    Modules/CoordinateMeasure/simginfo.h

FORMS    += \
    Modules/ImageExInfos/simageexinfos.ui \
    Modules/FileNameFactor/sfilenamefactor.ui \
    Modules/MainUi/smainwidget.ui \
    Modules/FilesReplace/sfilesreplace.ui \
    Modules/CoordinateMeasure/scoordinatemeasure.ui

