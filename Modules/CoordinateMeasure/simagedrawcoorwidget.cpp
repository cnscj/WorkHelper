#include "simagedrawcoorwidget.h"

SImageDrawCoorWidget::SImageDrawCoorWidget(QWidget *parent)
    :SImageDrawWidget(parent)
{

}

SImageDrawCoorWidget::~SImageDrawCoorWidget()
{

}

void SImageDrawCoorWidget::mousePressEvent(QMouseEvent *e)
{
    SImageDrawWidget::mousePressEvent(e);
}

void SImageDrawCoorWidget::mouseMoveEvent(QMouseEvent *e)
{
    SImageDrawWidget::mouseMoveEvent(e);
}

void SImageDrawCoorWidget::mouseReleaseEvent(QMouseEvent *e)
{
    SImageDrawWidget::mouseReleaseEvent(e);
}
