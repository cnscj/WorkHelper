#include "simagedrawexinfowidget.h"

SImageDrawExInfoWidget::SImageDrawExInfoWidget(QWidget *parent)
    :SImageDrawWidget(parent)
{

}

SImageDrawExInfoWidget::~SImageDrawExInfoWidget()
{

}

void SImageDrawExInfoWidget::mousePressEvent(QMouseEvent *event)
{
    auto point = event->pos();
    SImageDrawWidget::mousePressEvent(event);
}
