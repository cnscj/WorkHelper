#include "QPointWidget.h"
QPointWidget::QPointWidget(QWidget *parent)
: QAbstractButton(parent),m_pShaperData(nullptr),m_bIsCanDrag(false)
{

}

QPointWidget::~QPointWidget()
{

}

void QPointWidget::setPosition(const QPoint &p)
{
    QAbstractButton::move(p);
}

QPoint QPointWidget::getPosition()const
{
    return  QAbstractButton::pos();
}

void QPointWidget::setSize(const QSize &size)
{
    m_size = size;
}

QColor QPointWidget::getSize()const
{
    return m_size;
}


void QPointWidget::setShape(const QPointWidget::Shape shape,void *data)
{
    m_shaper = shape;
    m_pShaperData = data;
}

QPointWidget::Shape QPointWidget::getShape() const
{
    return m_shaper;
}
const void *QPointWidget::getShapeData()const
{
    return m_pShaperData;
}
void *QPointWidget::setShapeData(void *data)
{
   m_pShaperData = data;
}


void QPointWidget::setDragEnabled(bool isCanDrag)
{
    m_bIsCanDrag = isCanDrag;
}

bool QPointWidget::getDragEnabled()const
{
    return m_bIsCanDrag;
}

//////////////
////////////////
void QPointWidget::paintEvent(QPaintEvent *e)
{
    QAbstractButton::paintEvent(e);
}

void QPointWidget::mousePressEvent(QMouseEvent *e)
{

    QAbstractButton::mousePressEvent(e);
}

void QPointWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (m_bIsCanDrag)
    {
        if (event->buttons() & Qt::LeftButton)
        {
            auto pos = e->pos();
            setPosition(pos);
        }
    }
    QAbstractButton::mouseMoveEvent(e);
}

void QPointWidget::mouseReleaseEvent(QMouseEvent *e)
{

    QAbstractButton::mouseReleaseEvent(e);
}
