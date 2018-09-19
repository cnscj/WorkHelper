#include "SImageWidget.h"
#include <QFile>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QPaintEvent>
SImageWidget::SImageWidget(QWidget *parent)
    : QLabel(parent),m_curScale(1.0f),m_curBgColor(Qt::transparent)
{

}

SImageWidget::~SImageWidget()
{

}

const QImage *SImageWidget::image()const
{
    return &m_curImage;
}

int SImageWidget::contentWidth()const
{
    return (image()->width() * this->getScale());

}
int SImageWidget::contentHeight()const
{
    return (image()->height() * this->getScale());
}
QSize SImageWidget::contentSize()const
{
    return QSize(this->contentWidth(),this->contentHeight());
}

QRect SImageWidget::contentRect()const
{
    return QRect((this->width()-this->contentWidth())/2,(this->height()-this->contentHeight())/2,this->contentWidth(),this->contentHeight());
}
QPoint SImageWidget::contentPixelPos(int x,int y)const
{
    return QPoint(x/this->getScale(),y/this->getScale());
}
QPoint SImageWidget::contentPixelPos(const QPoint &p)const
{
    return contentPixelPos(p.x(),p.y());
}
QRgb SImageWidget::contentPixel(int x,int y)const
{
    auto scalePoint = this->contentPixelPos(x,y);
    return image()->pixel(scalePoint.x(),scalePoint.y());
}

QRgb SImageWidget::contentPixel(const QPoint &p)const
{
    return contentPixel(p.x(),p.y());
}
//
void SImageWidget::showBackgroundColor(const QColor &color)
{
    QPalette palette;
    palette.setColor(QPalette::Background, color);
    QLabel::setAutoFillBackground(true);  //一定要这句，否则不行
    QLabel::setPalette(palette);
}

void SImageWidget::showImage(const QString &filePath)
{
    if (QFile::exists(filePath))
    {
        QLabel::setAlignment(Qt::AlignCenter);      //居中
        drawPixmap((QImage *)image(),filePath);
    }
    else
    {
        drawPixmap(nullptr);
    }

}
///
void SImageWidget::setScale(float scale)
{
    if (image()->isNull()) return ;

    m_curScale = scale;
    m_curScale = m_curScale > 15.f ? 15.f : m_curScale;
    m_curScale = m_curScale < 0.05f ? 0.05f : m_curScale;
}
float SImageWidget::getScale() const
{
    return m_curScale;
}

void SImageWidget::setBackground(const QColor &color)
{
    m_curBgColor = color;
}
const QColor &SImageWidget::getBackground() const
{
    return m_curBgColor;
}

//
void SImageWidget::drawPixmap(const QImage *img)
{

    if (img && !img->isNull())
    {
        QPixmap pixmap(QPixmap::fromImage(*img));
        QLabel::setPixmap(pixmap.scaled(m_curImage.width()*m_curScale, m_curImage.height()*m_curScale,Qt::KeepAspectRatio));
    }
    else
    {
        QPixmap pixmap;
        QLabel::setPixmap(pixmap);
    }
}
void SImageWidget::drawPixmap(QImage *img,const QString &filePath)
{
    if (img)
    {
        img->load(filePath);
        drawPixmap(img);
    }
}
///
void SImageWidget::paintEvent(QPaintEvent *e)
{
    //画出背景色
    QPainter painter(this);
    QRect imgRect = this->contentRect();
    painter.fillRect(imgRect,QBrush(m_curBgColor));

    QLabel::paintEvent(e);
}

void SImageWidget::wheelEvent(QWheelEvent * event)
{

    int numDegress = event->delta();
    if (numDegress > 0)
    {
        setScale(getScale()*1.15f);
    }
    else
    {
        setScale(getScale()/1.15f);
    }
    drawPixmap(image());
}

void SImageWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::MiddleButton)
    {
        setScale(1.0f);
        drawPixmap(image());
    }
}
