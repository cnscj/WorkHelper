#include "SPointWidget.h"
#include <QMouseEvent>
SPointWidget::SPointWidget(QWidget *parent)
: QAbstractButton(parent),m_pShaperData(nullptr),m_bIsCanDrag(false)
{

}

SPointWidget::~SPointWidget()
{

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
}

QSize SPointWidget::getSize()const
{
    return m_size;
}


void SPointWidget::setShape(const SPointWidget::Shape shape,void *data)
{
    m_shaper = shape;
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
