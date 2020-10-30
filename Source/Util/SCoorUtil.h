#ifndef SCOORUTIL_H
#define SCOORUTIL_H

#include <QPoint>
#include <QRect>
namespace SCoorUtil
{
    //取得能在中点的左上角坐标
    QPoint getBoxInBoxCenterPos(const QRect &a,const QRect &b);
}

#endif // SCOORUTIL_H
