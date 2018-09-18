#ifndef SWIDGETUTIL_H
#define SWIDGETUTIL_H
#include <QPoint>
#include <QWidget>
namespace SWidgetUtil
{
    //开启关闭鼠标追踪
    void setMouseTrackingState(QWidget &widget,bool state);

    //取得中心坐标
    QPoint getCenterPos(const QWidget &widget);

    //
    QPoint makeMeInCenter(QWidget &child,const QWidget &father);


}
#endif // SWIDGETUTIL_H
