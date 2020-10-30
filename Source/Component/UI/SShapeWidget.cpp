#include "SShapeWidget.h"
#include <QMouseEvent>
#include <QPainter>
SShapeWidget::SShapeWidget(QWidget *parent)
: QWidget(parent),m_pShaperData(nullptr),m_bIsCanDrag(false)
{
    setShape(SShapeWidget::Shape::Elliptic,new QColor(255,0,0));
    setSize(QSize(6,6));
    SShapeWidget::setSizePolicy(QSizePolicy::Policy::Fixed,QSizePolicy::Policy::Fixed);
}

SShapeWidget::~SShapeWidget()
{
    delete m_pShaperData;
}

void SShapeWidget::setPosition(const QPoint &p)
{
    SShapeWidget::move(p);
}

QPoint SShapeWidget::getPosition()const
{
    return  SShapeWidget::pos();
}

void SShapeWidget::setSize(const QSize &size)
{
    m_size = size;
    SShapeWidget::setGeometry(QRect(getPosition().x(),getPosition().y(),m_size.width(),m_size.height()));
}

QSize SShapeWidget::getSize()const
{
    return m_size;
}


void SShapeWidget::setShape(const SShapeWidget::Shape shape,void *data)
{
    m_shaper = shape;
    if (m_pShaperData)
    {
        delete m_pShaperData;
        m_pShaperData = nullptr;
    }
    if (!data)
    {
        //TODO:
        switch(shape)
        {
            case SShapeWidget::Shape::Elliptic:
            {
                data = new QColor(255,0,0);
            }break;
            default:break;
        }
    }

    m_pShaperData = data;
}

SShapeWidget::Shape SShapeWidget::getShape() const
{
    return m_shaper;
}
const void *SShapeWidget::getShapeData()const
{
    return m_pShaperData;
}
void SShapeWidget::setShapeData(void *data)
{
   m_pShaperData = data;
}


void SShapeWidget::setDragEnabled(bool isCanDrag)
{
    m_bIsCanDrag = isCanDrag;
}

bool SShapeWidget::getDragEnabled()const
{
    return m_bIsCanDrag;
}
//
void SShapeWidget::paint(QPainter &painter)
{
    switch(m_shaper)
    {
        case SShapeWidget::Shape::Elliptic:
        {
            auto size = getSize();
            auto color = (QColor *)getShapeData();
            auto old = painter.brush();

            painter.setBrush(QBrush(*color));
            painter.drawEllipse(QPoint(size.width()/2,size.height()/2),size.width()/2,size.height()/2);
            painter.setBrush(old);
        }break;
        case SShapeWidget::Shape::Rect:
        {
            auto size = getSize();
            auto color = (QColor *)getShapeData();
            auto old = painter.brush();

            painter.setBrush(QBrush(*color));
            painter.drawRect(QRect(size.width()/2,size.height()/2,size.width()/2,size.height()/2));
            painter.setBrush(old);
        }break;
        case SShapeWidget::Shape::Image:
        {
            auto size = getSize();
            auto data = (QImage *)getShapeData();

            painter.drawImage(QRect(size.width()/2,size.height()/2,size.width()/2,size.height()/2),*data);
        }break;
    }
}
//////////////
////////////////

void SShapeWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    paint(painter);

    QWidget::paintEvent(e);
}

void SShapeWidget::mousePressEvent(QMouseEvent *e)
{

    QWidget::mousePressEvent(e);
}

void SShapeWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (m_bIsCanDrag)
    {
        if (e->buttons() & Qt::LeftButton)
        {
            auto pos = QPoint(e->x(),e->y());
            setPosition(pos);
            return;
        }
    }
    QWidget::mouseMoveEvent(e);
}

void SShapeWidget::mouseReleaseEvent(QMouseEvent *e)
{

    QWidget::mouseReleaseEvent(e);
}
