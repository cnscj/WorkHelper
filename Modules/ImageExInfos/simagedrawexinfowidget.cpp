#include "simagedrawexinfowidget.h"
#include <QMouseEvent>
SImageDrawExInfoWidget::SImageDrawExInfoWidget(QWidget *parent)
    :SImageDrawWidget(parent)
{

}

SImageDrawExInfoWidget::~SImageDrawExInfoWidget()
{

}

void SImageDrawExInfoWidget:: mousePressEvent(QMouseEvent *e)
{
     SImageDrawWidget::mousePressEvent(e);
}

void SImageDrawExInfoWidget::mouseMoveEvent(QMouseEvent *e)
{

    SImageDrawWidget::mousePressEvent(e);
}

void SImageDrawExInfoWidget::mouseReleaseEvent(QMouseEvent *e)
{
    QPoint point = e->pos();
    this->addPoint(point);
    qDebug("%d,%d",point.x(),point.y());
    SImageDrawWidget::mouseReleaseEvent(e);
}

