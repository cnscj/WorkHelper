#include "Base/SMarkPoint.h"


SMarkPoint::SMarkPoint(const QPoint &p,int size,Qt::GlobalColor color):
    m_MarkPos(p),m_MarkSize(size),m_MarkColor(color)
{

}
SMarkPoint::~SMarkPoint()
{

}

void SMarkPoint::setMarkPos(const QPoint &p)
{
    m_MarkPos = p;
}
const QPoint &SMarkPoint::getMarkPos()
{
    return m_MarkPos;
}

void SMarkPoint::setMarkSize(int size)
{
    m_MarkSize = size;
}
const int &SMarkPoint::getMarkSize()
{
    return m_MarkSize;
}


void SMarkPoint::setMarkColor(Qt::GlobalColor color)
{
    m_MarkColor = color;
}
const Qt::GlobalColor &SMarkPoint::getMarkColor()
{
    return m_MarkColor;
}
