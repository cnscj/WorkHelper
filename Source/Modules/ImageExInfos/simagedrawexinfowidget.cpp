#include "simagedrawexinfowidget.h"
#include <QMouseEvent>
#include "Util/SPaintUtil.h"
SImageDrawExInfoWidget::SImageDrawExInfoWidget(QWidget *parent)
    :SImageDrawWidget(parent),m_bIsCanMarkPoint(false)
{
    this->showAnchorPoint();
}

SImageDrawExInfoWidget::~SImageDrawExInfoWidget()
{

}

void SImageDrawExInfoWidget::markEnabled(bool state)
{
    m_bIsCanMarkPoint = state;
}

///

void SImageDrawExInfoWidget::paintEvent(QPaintEvent *e)
{
    SImageDrawWidget::paintEvent(e);
}

void SImageDrawExInfoWidget::mousePressEvent(QMouseEvent *e)
{
     SImageDrawWidget::mousePressEvent(e);
}

void SImageDrawExInfoWidget::mouseMoveEvent(QMouseEvent *e)
{

    SImageDrawWidget::mousePressEvent(e);
}

void SImageDrawExInfoWidget::mouseReleaseEvent(QMouseEvent *e)
{
    if (m_bIsCanMarkPoint)
    {
        QPoint point = e->pos();
        QPoint fixPoint = this->contentPixelPos(point);//存在倍数的误差
        this->setPaintType(PaintType::Polygon);
        this->addPaintPoint(fixPoint);
        return; //防止穿透
    }

    SImageDrawWidget::mouseReleaseEvent(e);
}

