#ifndef SIMGINFO_H
#define SIMGINFO_H
#include <QRgb>
typedef struct tagImgInfo
{
    int pixelX;
    int pixelY;
    int mouseX;                  //鼠标坐标x
    int mouseY;                  //鼠标坐标y
    float scale;                //缩放倍率
    int width;
    int height;
    QRgb  pixel;                 //当前像素

}SImgInfo;

#endif // SIMGINFO_H
