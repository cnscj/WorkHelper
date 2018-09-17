#include "sscrollareacontentwidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QPaintEvent>
#include "Util/SWidgetUtil.h"

SScrollAreaContentWidget::SScrollAreaContentWidget(QWidget *parent)
    :SImageDrawWidget(parent)
{


}

SScrollAreaContentWidget::~SScrollAreaContentWidget()
{

}

void SScrollAreaContentWidget::paintEvent(QPaintEvent *e)
{
    SImageDrawWidget::paintEvent(e);

    QPainter painter(this);
    QPoint &curPos = m_curPoint;
    QSize size = this->size();
    painter.setBrush(QBrush(Qt::red));
    painter.drawEllipse(curPos,1,1);
    painter.setPen(QPen(Qt::black,1,Qt::SolidLine));
    QLineF line(curPos.x()-size.width(),curPos.y(),curPos.x()+size.width(),curPos.y());
    painter.drawLine(line);
    painter.setPen(QPen(Qt::black,1,Qt::SolidLine));
    QLineF line1(curPos.x(),curPos.y()-size.height(),curPos.x(),curPos.y()+size.height());
    painter.drawLine(line1);


}

void SScrollAreaContentWidget::enterEvent(QEvent *e)
{
    SWidgetUtil::setMouseTrackingState(this,true);
}

void SScrollAreaContentWidget::mouseMoveEvent(QMouseEvent *e)
{
    m_curPoint = e->pos();
    SImageDrawWidget::repaint();

    //TODO:缩放还原
    SImgInfo info;
    info.x = m_curPoint.x();
    info.y = m_curPoint.y();
    emit position(info);

    SImageDrawWidget::mouseMoveEvent(e);
}


void SScrollAreaContentWidget::leaveEvent(QEvent *event)
{
   SWidgetUtil::setMouseTrackingState(this,false);
}
