#include "SPointWidget.h"
#include <QMouseEvent>
#include <QPainter>
SPointWidget::SPointWidget(QWidget *parent)
: QWidget(parent),m_pShaperData(nullptr),m_bIsCanDrag(false)
{
    setShape(SPointWidget::Shape::Elliptic,new QColor(255,0,0));
    setSize(QSize(6,6));
    QWidget::setSizePolicy(QSizePolicy::Policy::Fixed,QSizePolicy::Policy::Fixed);
}

SPointWidget::~SPointWidget()
{
    delete m_pShaperData;
}

void SPointWidget::setPosition(const QPoint &p)
{
    QWidget::move(p);
}

QPoint SPointWidget::getPosition()const
{
    return  QWidget::pos();
}

void SPointWidget::setSize(const QSize &size)
{
    m_size = size;
    QWidget::setGeometry(QRect(getPosition().x(),getPosition().y(),m_size.width(),m_size.height()));
}

QSize SPointWidget::getSize()const
{
    return m_size;
}


void SPointWidget::setShape(const SPointWidget::Shape shape,void *data)
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
            case SPointWidget::Shape::Elliptic:
            {
                data = new QColor(255,0,0);
            }break;
            default:break;
        }
    }

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
void SPointWidget::paint(QPainter &painter)
{
    switch(m_shaper)
    {
        case SPointWidget::Shape::Elliptic:
        {
            auto size = getSize();
            auto color = (QColor *)getShapeData();
            auto old = painter.brush();

            painter.setBrush(QBrush(*color));
            painter.drawEllipse(QPoint(size.width()/2,size.height()/2),size.width()/2,size.height()/2);
            painter.setBrush(old);
        }break;
        case SPointWidget::Shape::Rect:
        {
            auto size = getSize();
            auto color = (QColor *)getShapeData();
            auto old = painter.brush();

            painter.setBrush(QBrush(*color));
            painter.drawRect(QRect(size.width()/2,size.height()/2,size.width()/2,size.height()/2));
            painter.setBrush(old);
        }break;
        case SPointWidget::Shape::Image:
        {
            auto size = getSize();
            auto data = (QImage *)getShapeData();

            painter.drawImage(QRect(size.width()/2,size.height()/2,size.width()/2,size.height()/2),*data);
        }break;
    }
}
//////////////
////////////////

void SPointWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    paint(painter);

    QWidget::paintEvent(e);
}

void SPointWidget::mousePressEvent(QMouseEvent *e)
{

    QWidget::mousePressEvent(e);
}

void SPointWidget::mouseMoveEvent(QMouseEvent *e)
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

void SPointWidget::mouseReleaseEvent(QMouseEvent *e)
{

    QWidget::mouseReleaseEvent(e);
}
