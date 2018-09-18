#include "SImageDrawWidget.h"
#include "../SDrawTool.h"
SImageDrawWidget::SImageDrawWidget(QWidget *parent)
: SImageWidget(parent)
{

}

SImageDrawWidget::~SImageDrawWidget()
{

}

void SImageDrawWidget::paintEvent(QPaintEvent *e)
{

    SImageWidget::paintEvent(e);
//    //创建一块画布,缓存信息
//    QPixmap pixmap(image()->size());
//    QPainter painter;
//    painter.begin(&pixmap);
//    //TODO:直接画在上面

//    painter.end();




}
