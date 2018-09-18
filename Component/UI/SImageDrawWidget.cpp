#include "SImageDrawWidget.h"

SImageDrawWidget::SImageDrawWidget(QWidget *parent)
: SImageWidget(parent)
{

}

SImageDrawWidget::~SImageDrawWidget()
{

}

void SImageDrawWidget::paintEvent(QPaintEvent *e)
{

    QPainter painter(this);

    SImageWidget::paintEvent(e);

}
