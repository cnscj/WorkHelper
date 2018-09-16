#include "SImageDrawWidget.h"
#include "../SDrawTool.h"
SImageDrawWidget::SImageDrawWidget(QWidget *parent)
: SImageView(parent)
{

}

SImageDrawWidget::~SImageDrawWidget()
{

}

void SImageDrawWidget::addPoint(const QPoint &p)
{
    m_drawTool.addPoint(p);
}

void SImageDrawWidget::drawPoints(QPainter &painter)
{
   m_drawTool.drawPoints(&painter);
}

void SImageDrawWidget::drawPolygon(QPainter &painter)
{
    m_drawTool.drawPolygon(&painter);
}

void SImageDrawWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    drawPoints(painter);
    SImageView::paintEvent(e);

}
