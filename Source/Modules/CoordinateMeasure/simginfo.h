#ifndef SIMGINFO_H
#define SIMGINFO_H
#include <QRgb>
#include <QPoint>
#include <QPointF>
#include <QSize>
typedef struct tagImgInfo
{
    QPoint pixelPos;            //像素坐标
    QPoint mousePos;            //鼠标坐标
    QPointF anchorPoint;        //锚点
    QSize size;                 //图像大小
    QRgb  pixel;                //当前像素

    float scale;                //缩放倍率
}SImgInfo;

#endif // SIMGINFO_H
