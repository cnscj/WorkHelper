#include "SPointWidget.h"
#include <QMouseEvent>
#include <QPainter>
SPointWidget::SPointWidget(QWidget *parent)
: QAbstractButton(parent),m_size(1,1),m_pShaperData(nullptr),m_bIsCanDrag(false)
{
    setShape(SPointWidget::Shape::Elliptic,new QColor(255,0,0));
    QAbstractButton::setSizePolicy(QSizePolicy::Policy::Fixed,QSizePolicy::Policy::Fixed);
}

SPointWidget::~SPointWidget()
{
    delete m_pShaperData;
}

void SPointWidget::setPosition(const QPoint &p)
{
    QAbstractButton::move(p);
}

QPoint SPointWidget::getPosition()const
{
    return  QAbstractButton::pos();
}

void SPointWidget::setSize(const QSize &size)
{
    m_size = size;
    QAbstractButton::setGeometry(QRect(getPosition().x(),getPosition().y(),size.width(),size.height()));
}

QSize SPointWidget::getSize()const
{
    return m_size;
}


void SPointWidget::setShape(const SPointWidget::Shape shape,void *data)
{
    m_shaper = shape;
    if (m_pShaperData)delete m_pShaperData;
    m_pShaperData = data;
}

SPointWidget::Shape SPointWidget::getShape() const
{
    return m_shaper;
}
const void *SPointWidget::getShapeData()const
{
    return m_pShaperData;
}
void SPointWidget::setShapeData(void *data)
{
   m_pShaperData = data;
}


void SPointWidget::setDragEnabled(bool isCanDrag)
{
    m_bIsCanDrag = isCanDrag;
}

bool SPointWidget::getDragEnabled()const
{
    return m_bIsCanDrag;
}
//
void SPointWidget::draw(QPainter *pPainter)
{
    switch(m_shaper)
    {
        case SPointWidget::Shape::Elliptic:
        {
            auto pos = getPosition();
            auto size = getSize();
            auto color = (QColor *)getShapeData();
            auto old = pPainter->brush();

            pPainter->setBrush(QBrush(*color));
            pPainter->drawEllipse(pos,size.width(),size.height());
            pPainter->setBrush(old);
        }break;
        case SPointWidget::Shape::Rect:
        {
            auto pos = getPosition();
            auto size = getSize();
            auto color = (QColor *)getShapeData();
            auto old = pPainter->brush();

            pPainter->setBrush(QBrush(*color));
            pPainter->drawRect(QRect(pos.x(),pos.y(),size.width(),size.height()));
            pPainter->setBrush(old);
        }break;
        case SPointWidget::Shape::Image:
        {
            auto pos = getPosition();
            auto size = getSize();
            auto data = (QImage *)getShapeData();

            pPainter->drawImage(QRect(pos.x(),pos.y(),size.width(),size.height()),*data);
        }break;
    }
}
//////////////
////////////////



void SPointWidget::mousePressEvent(QMouseEvent *e)
{

    QAbstractButton::mousePressEvent(e);
}

void SPointWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (m_bIsCanDrag)
    {
        if (e->buttons() & Qt::LeftButton)
        {
            auto pos = QPoint(e->x(),e->y());
            setPosition(pos);
        }
    }
    QAbstractButton::mouseMoveEvent(e);
}

void SPointWidget::mouseReleaseEvent(QMouseEvent *e)
{

    QAbstractButton::mouseReleaseEvent(e);
}
