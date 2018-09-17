#include "SWidgetUtil.h"
#include <QWidget>
void SWidgetUtil::setMouseTrackingState(QWidget *child,bool state)
{
    //开启\关闭鼠标追踪-需要一层层打开
    for(QWidget *widget = child ; widget ; widget = widget->parentWidget())
    {
        widget->setMouseTracking(state);
    };
}
