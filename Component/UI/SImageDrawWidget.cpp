#include "SImageDrawWidget.h"
#include <QPainter>
#include "Util/SPaintUtil.h"
SImageDrawWidget::SImageDrawWidget(QWidget *parent)
    : SImageWidget(parent),m_curPaintType(SImageDrawWidget::PaintType::None)
{

}

SImageDrawWidget::~SImageDrawWidget()
{

}
//

const QVector<QPoint> &SImageDrawWidget::getPaintPoints()const
{
    return m_curPoints;
}
void SImageDrawWidget::setPaintPoints(QVector<QPoint> &points)
{
    m_curPoints = points;
}

void SImageDrawWidget::addPaintPoint(const QPoint &p)
{
    m_curPoints.push_back(p);
    this->repaint();
}

SImageDrawWidget::PaintType SImageDrawWidget::getPaintType()const
{
    return m_curPaintType;
}
void SImageDrawWidget::setPaintType(const SImageDrawWidget::PaintType type)
{
    m_curPaintType = type;
}
void SImageDrawWidget::paint(QVector<QPoint> &points,const PaintType type)
{
    setPaintPoints(points);
    setPaintType(type);
    this->repaint();
}

void SImageDrawWidget::clear()
{
    m_curPoints.clear();
    m_curPaintType = PaintType::None;
}
//

void SImageDrawWidget::paintEvent(QPaintEvent *e)
{
    SImageWidget::paintEvent(e);
    switch(m_curPaintType)
    {
        case SImageDrawWidget::PaintType::Points:
        {
             QPainter painter(this);
             SPaintUtil::drawPoints(painter,m_curPoints);
        }break;
        case SImageDrawWidget::PaintType::Polygon:
        {
             QPainter painter(this);
             SPaintUtil::drawPolygon(painter,m_curPoints);
        }break;
        default:break;
    }



}
