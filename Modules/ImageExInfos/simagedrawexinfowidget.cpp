#include "simagedrawexinfowidget.h"
#include <QMouseEvent>
#include "Util/SPaintUtil.h"
SImageDrawExInfoWidget::SImageDrawExInfoWidget(QWidget *parent)
    :SImageDrawWidget(parent),m_bIsCanMarkPoint(false)
{

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
        this->setPaintType(PaintType::Polygon);
        this->addPaintPoint(point);
    }

    SImageDrawWidget::mouseReleaseEvent(e);
}

