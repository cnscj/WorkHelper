#include "sscrollareacontentwidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QPaintEvent>
#include "Util/SWidgetUtil.h"

SScrollAreaContentWidget::SScrollAreaContentWidget(QWidget *parent)
    :SImageDrawWidget(parent),m_isWantScalel(false),m_isCanMove(true),m_isWantResetAnchorPoint(false)
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
    QSize size = this->size();
    float fscale = SImageDrawWidget::getScale();
    //抓取
    if (this->pixmap())
    {
        QRect imgRect = this->contentRect();/*((this->width()-this->pixmap()->width())/2, (this->height()-this->pixmap()->height())/2,this->pixmap()->width(),this->pixmap()->height());*/
        QPoint srcCoorPos = this->contentPixmapPos(curPos);/*curPos.x() - imgRect.x(),curPos.y() - imgRect.y());*/
        if (imgRect.contains(curPos,false))//预防越界,
        {
            m_curInfo.pixel = this->pixmap()->toImage().pixel(srcCoorPos.x(),srcCoorPos.y());//取得当前画布像素
            m_curInfo.pixelPos = this->contentPixelPosAR(curPos);
            m_curInfo.size = this->image()->size();
        }

    }

    //绘制十字线
    QPainter painter(this);
    painter.setBrush(QBrush(Qt::red));
    painter.drawEllipse(curPos,1,1);
    painter.setPen(QPen(Qt::black,1,Qt::SolidLine));
    QLineF line(curPos.x()-size.width(),curPos.y(),curPos.x()+size.width(),curPos.y());
    painter.drawLine(line);
    painter.setPen(QPen(Qt::black,1,Qt::SolidLine));
    QLineF line1(curPos.x(),curPos.y()-size.height(),curPos.x(),curPos.y()+size.height());
    painter.drawLine(line1);

    //绘制目标锚点
    if (m_isWantResetAnchorPoint)
    {
        painter.setBrush(QBrush(Qt::green));
        painter.drawEllipse(curPos,3,3);
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
    //TODO:此处应该记录坐标而不是不绘制,不然放大失效
    if (m_isCanMove)
    {
        m_curPoint = e->pos();

        m_curInfo.mousePos = m_curPoint;

        if (m_isWantResetAnchorPoint)
        {
            QPoint pixmapPos = this->contentPixmapPos(m_curPoint);
            QSize conetntSize = this->contentSize();
            m_destARPoint = QPointF((float)pixmapPos.x()/conetntSize.width(),(float)pixmapPos.y()/conetntSize.height());

        }

        SImageDrawWidget::repaint();
    }
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
     SImageDrawWidget::mousePressEvent(e);
}

void SScrollAreaContentWidget::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        m_isCanMove = !m_isCanMove;
    }
    SImageDrawWidget::mouseReleaseEvent(e);
}
