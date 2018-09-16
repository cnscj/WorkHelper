#include "SImageDrawWidget.h"
#include "../SDrawTool.h"
SImageDrawWidget::SImageDrawWidget(QWidget *parent)
: SImageView(parent)
{

}

SImageDrawWidget::~SImageDrawWidget()
{

}

void SImageDrawWidget::drawPoint(const QPoint &p)
{
    m_drawTool.addPoint(p);
}

void SImageDrawWidget::paintEvent(QPaintEvent *e)
{
   SImageView::paintEvent(e);
}
