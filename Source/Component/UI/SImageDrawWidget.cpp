#include "SImageDrawWidget.h"
#include <QPainter>
#include "Util/SPaintUtil.h"
SImageDrawWidget::SImageDrawWidget(QWidget *parent)
    : SImageWidget(parent),m_curPaintType(SImageDrawWidget::PaintType::None),m_isShowAnchorPoint(false)
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
void SImageDrawWidget::showAnchorPoint()
{
    m_isShowAnchorPoint = true;
    this->repaint();
}
void SImageDrawWidget::hideAnchorPoint()
{
    m_isShowAnchorPoint = false;
    this->repaint();
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

    if (image() && !image()->isNull())
    {
        //解决方法:新建原图大小,画,然后做同等的缩放
        QPixmap pixmap(image()->size());
        pixmap.fill(Qt::transparent);
        //QPixmap pixmap(QPixmap::fromImage(*image()));
        QPainter painter(&pixmap);
        switch(m_curPaintType)
        {
            case SImageDrawWidget::PaintType::Points:
            {
                 SPaintUtil::drawPoints(painter,m_curPoints);
            }break;
            case SImageDrawWidget::PaintType::Polygon:
            {
                 SPaintUtil::drawPolygon(painter,m_curPoints);
            }break;
            default:break;
        }
        //绘制锚点
        if (m_isShowAnchorPoint)
        {
            SPaintUtil::drawPoint(painter,this->getARPos(),2);
        }

        QPainter widgetPainter(this);
        widgetPainter.drawPixmap(this->contentRect(),pixmap.scaled(this->contentSize(),Qt::KeepAspectRatio));
    }

}
