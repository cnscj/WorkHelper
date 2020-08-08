#-------------------------------------------------
#
# Project created by QtCreator 2018-09-07T14:44:45
#
#-------------------------------------------------

QT       += core xml
QT       += core gui
ICON    = myicon.icns
RC_ICONS = myicon.ico
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
    Component/UI/SPictureBox.cpp \
    Util/SCoorUtil.cpp \
    Util/SColorUtil.cpp \
    Component/UI/SShapeWidget.cpp \
    Component/UI/SRectWidget.cpp \
    Modules/FGUIToxLua/sfguitoxlua.cpp \
    Modules/FGUIToxLua/Component/sfguiobjectitem.cpp \
    Modules/FGUIToxLua/Model/SFGUIObjectItemData.cpp \
    Modules/U9Inject/su9Inject.cpp \
    Component/SAdbHelper.cpp

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
    Modules/CoordinateMeasure/simginfo.h \
    Util/SCoorUtil.h \
    Util/SColorUtil.h \
    Component/UI/SShapeWidget.h \
    Component/UI/SRectWidget.h \
    Modules/FGUIToxLua/sfguitoxlua.h \
    Modules/FGUIToxLua/Component/sfguiobjectitem.h \
    Modules/FGUIToxLua/Model/SFGUIObjectItemData.h \
    Modules/U9Inject/su9Inject.h \
    Component/SAdbHelper.h

FORMS    += \
    Modules/ImageExInfos/simageexinfos.ui \
    Modules/FileNameFactor/sfilenamefactor.ui \
    Modules/MainUi/smainwidget.ui \
    Modules/FilesReplace/sfilesreplace.ui \
    Modules/CoordinateMeasure/scoordinatemeasure.ui \
    Modules/FGUIToxLua/sfguitoxlua.ui \
    Modules/FGUIToxLua/Component/sfguiobjectitem.ui \
    Modules/U9Inject/su9inject.ui

