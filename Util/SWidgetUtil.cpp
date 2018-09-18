#include "SWidgetUtil.h"

void SWidgetUtil::setMouseTrackingState(QWidget &widget,bool state)
{
    //开启\关闭鼠标追踪-需要一层层打开
    for(QWidget *p = &widget ; p ; p = p->parentWidget())
    {
        p->setMouseTracking(state);
    };
}

QPoint SWidgetUtil::getCenterPos(const QWidget &widget)
{
    return QPoint(widget.width()/2,widget.height()/2);
}

QPoint SWidgetUtil::makeMeInCenter(QWidget &child,const QWidget &father)
{
    QPoint center((father.width()-child.width())/2,(father.height()-child.height())/2);
    child.move(center);
    return center;
}
