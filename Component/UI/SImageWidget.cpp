#include "SImageWidget.h"
#include <QFile>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QPaintEvent>
SImageWidget::SImageWidget(QWidget *parent)
    : QLabel(parent),m_curScale(1.0f)
{

}

SImageWidget::~SImageWidget()
{

}

const QImage *SImageWidget::image()const
{
    return &m_curImage;
}

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
float SImageWidget::getScale()
{
    return m_curScale;
}

void SImageWidget::setBackground(const QColor &color)
{
    m_curBgColor = color;
}
const QColor &SImageWidget::getBackground()
{
    return m_curBgColor;
}

//
void SImageWidget::drawPixmap(const QImage *img)
{
    if (img)
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
 //TODO:画出背景色
//    QPainter painter(this);
//    painter.setBackground(QBrush(m_curBgColor));
//    painter.fillRect(QRect(0,0,image()->width(),image()->height()),QBrush(m_curBgColor));

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
