#ifndef UIMODULES_H
#define UIMODULES_H
#include <functional>

#include <QString>
#include <QWidget>
#include <QList>

#include "Modules/MainUi/smainwidget.h"

#include "Modules/FileNameFactor/sfilenamefactor.h"
#include "Modules/ImageExInfos/simageexinfos.h"
#include "Modules/FilesReplace/sfilesreplace.h"
#include "Modules/CoordinateMeasure/scoordinatemeasure.h"
#include "Modules/FGUIToxLua/sfguitoxlua.h"
#include "Modules/U9Inject/su9Inject.h"

typedef struct
{
    int index;
    QString title;
    QString desc;
    std::function<QWidget *(void)> createWidget;
}MODULE_INFOS;

//模块添加:
static const MODULE_INFOS MODULES[]=
{
//    {0,"文件路径生成","为资源文件生成Lua代码",[](){return new SFileNameFactor();}},
//    {1,"图像附加信息","给图像附加信息,导出Lua代码",[](){return new SImageExInfos();}},
    {2,"文件批量替换","批量替换资源文件",[](){return new SFilesReplace();}},
    {3,"图像坐标测量","测量UI控件坐标",[](){return new SCoordinateMeasure();}},
    {4,"FGUI生成xLua代码","生成UI代码",[](){return new SFGUIToxLua();}},
    {5,"U9注入调试","U9注入调试",[](){return new SU9Inject();}},
};

#endif // UIMODULES_H
