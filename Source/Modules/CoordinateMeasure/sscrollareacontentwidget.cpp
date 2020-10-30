#include "sscrollareacontentwidget.h"
#include <cmath>
#include <QPainter>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QApplication>
#include "Util/SWidgetUtil.h"

SScrollAreaContentWidget::SScrollAreaContentWidget(QWidget *parent)
    :SImageDrawWidget(parent),m_isWantScalel(false),m_isThumbtack(false),m_isWantResetAnchorPoint(false),m_isMoving(false)
{


}

SScrollAreaContentWidget::~SScrollAreaContentWidget()
{

}

void SScrollAreaContentWidget::paintEvent(QPaintEvent *e)
{
    //绘制图片
    SImageDrawWidget::paintEvent(e);

    //
    QPoint &curPos = m_curPoint;
    QPoint &curThumbtackPoint = m_thumbtackPoint;
    QSize size = this->size();
    float fscale = SImageDrawWidget::getScale();
    //抓取
    if (this->pixmap())
    {
        QRect imgRect = this->contentRect();/*((this->width()-this->pixmap()->width())/2, (this->height()-this->pixmap()->height())/2,this->pixmap()->width(),this->pixmap()->height());*/
        QPoint srcCoorPos = this->contentPixmapPos(curThumbtackPoint);/*curPos.x() - imgRect.x(),curPos.y() - imgRect.y());*/
        if (imgRect.contains(curThumbtackPoint,false))//预防越界,
        {
            m_curInfo.pixel = this->pixmap()->toImage().pixel(srcCoorPos.x(),srcCoorPos.y());//取得当前画布像素
            m_curInfo.pixelPos = this->contentPixelPosAR(curThumbtackPoint);
            m_curInfo.size = this->image()->size();
        }

    }

    //绘制十字线
    //TODO:将图钉坐标从视图坐标转为绘图坐标

    QPainter painter(this);
    painter.setBrush(QBrush(Qt::red));
    painter.drawEllipse(curThumbtackPoint,1,1);
    painter.setPen(QPen(Qt::black,1,Qt::SolidLine));
    QLineF line(curThumbtackPoint.x()-size.width(),curThumbtackPoint.y(),curThumbtackPoint.x()+size.width(),curThumbtackPoint.y());
    painter.drawLine(line);
    painter.setPen(QPen(Qt::black,1,Qt::SolidLine));
    QLineF line1(curThumbtackPoint.x(),curThumbtackPoint.y()-size.height(),curThumbtackPoint.x(),curThumbtackPoint.y()+size.height());
    painter.drawLine(line1);

    //绘制目标锚点
    if (m_isWantResetAnchorPoint)
    {
        painter.setBrush(QBrush(Qt::green));
        painter.drawEllipse(curPos,3,3);

    }

    //绘出矩形
    if (m_isMoving)
    {
        painter.setBrush(QBrush(Qt::transparent));
        painter.drawRect(m_dragRect);
        QPoint currectPos = this->contentPixelPosAR(m_dragRect.x(),m_dragRect.y());
        QSize currectSize = QSize(::fabs(m_dragRect.width()/this->getScale()),::fabs(m_dragRect.height()/this->getScale()));
        painter.drawText(m_dragRect.normalized(),Qt::AlignCenter,QString("%1,%2,%3,%4")
                         .arg(currectPos.x())
                         .arg(currectPos.y())
                         .arg(currectSize.width())
                         .arg(currectSize.height()));

    }
    m_curInfo.anchorPoint = SImageDrawWidget::getAnchorPoint();
    m_curInfo.scale = fscale;

    emit postInfo(m_curInfo);
}

void SScrollAreaContentWidget::enterEvent(QEvent *e)
{
    SWidgetUtil::setMouseTrackingState(*this,true);
    this->setFocus(Qt::MouseFocusReason);  //设置焦点
    SImageDrawWidget::enterEvent(e);
}

void SScrollAreaContentWidget::mouseMoveEvent(QMouseEvent *e)
{
    m_curPoint = e->pos();
    m_curInfo.mousePos = m_curPoint;

    //确保按住左键移动.
    QPoint temp = m_curPoint - m_dragPoint;
    if (e->buttons() & Qt::LeftButton && temp.manhattanLength() > QApplication::startDragDistance())   //只有这个长度大于默认的距离,才会被系统认为是形成拖拽的操作.
    {
        m_isMoving = true;
        m_isThumbtack = false;
        QSize size(temp.x(),temp.y());
        m_dragRect = QRect(m_dragPoint,size);
    }

    //此处应该记录坐标而不是不绘制,不然放大失效
    if (!m_isThumbtack)
    {
        m_thumbtackPoint = m_curPoint;
    }


    if (m_isWantResetAnchorPoint)
    {
        QPoint pixmapPos = this->contentPixmapPos(m_curPoint);
        QSize conetntSize = this->contentSize();
        m_destARPoint = QPointF((float)pixmapPos.x()/conetntSize.width(),(float)pixmapPos.y()/conetntSize.height());
    }

    SImageDrawWidget::repaint();
    SImageDrawWidget::mouseMoveEvent(e);
}


void SScrollAreaContentWidget::leaveEvent(QEvent *e)
{
   SWidgetUtil::setMouseTrackingState(*this,false);
   this->clearFocus();                  //失去焦点
   SImageDrawWidget::leaveEvent(e);
}

//
void SScrollAreaContentWidget::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Control || e->key() == Qt::Key_Comma)
    {
        m_isWantResetAnchorPoint = true;
        QPoint pixmapPos = this->contentPixmapPos(m_curPoint);
        QSize conetntSize = this->contentSize();
        m_destARPoint = QPointF((float)pixmapPos.x()/conetntSize.width(),(float)pixmapPos.y()/conetntSize.height());
        this->repaint();
    }
    if (e->key() == Qt::Key_Option || e->key() == Qt::Key_Alt)
    {
        m_isWantScalel = true;

    }
    SImageDrawWidget::keyPressEvent(e);
}

void SScrollAreaContentWidget::keyReleaseEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Control || e->key() == Qt::Key_Comma)
    {
        // 用于设立新锚点
        m_isWantResetAnchorPoint = false;
        this->setAnchorPoint(m_destARPoint);
        SImageDrawWidget::repaint();
    }
    else if (e->key() == Qt::Key_Option || e->key() == Qt::Key_Alt)
    {
        m_isWantScalel = false;
    }
    SImageDrawWidget::keyReleaseEvent(e);
}

void SScrollAreaContentWidget::wheelEvent(QWheelEvent *e)
{
    if (m_isWantScalel)
    {
        SImageDrawWidget::wheelEvent(e);
    }
}

void SScrollAreaContentWidget::mousePressEvent(QMouseEvent *e)
{
    //确保左键拖拽.
    if (e->button() == Qt::LeftButton)
    {
        //先保存拖拽的起点.
        m_dragPoint = e->pos();
    }
     SImageDrawWidget::mousePressEvent(e);
}

void SScrollAreaContentWidget::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        if (m_isMoving)
        {
            m_isThumbtack = false;
            m_isMoving = false;
        }
        else
        {
            m_isThumbtack = !m_isThumbtack;
        }
        this->repaint();
    }
    SImageDrawWidget::mouseReleaseEvent(e);
}
