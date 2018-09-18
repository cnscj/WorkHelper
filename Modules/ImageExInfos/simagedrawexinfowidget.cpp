#include "simagedrawexinfowidget.h"
#include <QMouseEvent>
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
        qDebug("%d,%d",point.x(),point.y());
    }

    SImageDrawWidget::mouseReleaseEvent(e);
}

