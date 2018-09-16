#include "SImageView.h"
#include <QWheelEvent>
SImageView::SImageView(QWidget *parent)
: QWidget(parent),m_gridLayout(this),m_curScale(1.0f)
{
    m_gridLayout.addWidget(&m_outLabel, 0, 0, 1, 1, Qt::AlignHCenter|Qt::AlignVCenter);


}

SImageView::~SImageView()
{

}

const QImage *SImageView::image()const
{
    return &m_curImage;
}

const QLabel *SImageView::label()const
{
    return &m_outLabel;
}


void SImageView::showImage(const QString &filePath)
{
    if (QFile::exists(filePath))
    {
        m_curImage.load(filePath);
        QPixmap pixmap(QPixmap::fromImage(m_curImage));
        m_outLabel.setPixmap(pixmap);
    }else
        m_outLabel.setPixmap(QPixmap());

}

void SImageView::setBackgroundColor(QColor color)
{
    QPalette palette;
    palette.setColor(QPalette::Background, color);
    m_outLabel.setAutoFillBackground(true);  //一定要这句，否则不行
    m_outLabel.setPalette(palette);
}

void SImageView::wheelEvent(QWheelEvent * event)
{
        // A positive value indicates that
        // the wheel was rotated forwards away from the user;
        // negative value indicates that
        // the wheel was rotated backwards toward the user.
        int numDegress = event->delta();
        // If numDegress > 0, then zoom in,
        // else, zoom out.
        // The scale control the picture's size
        if (numDegress > 0)
        {
            m_curScale *= 1.15f;
            m_curScale = m_curScale > 15.f ? 15.f : m_curScale;
        }
        else
        {
            m_curScale /= 1.15f;
            m_curScale = m_curScale < 0.05f ? 0.05f : m_curScale;
        }
        QPixmap pixmap(QPixmap::fromImage(m_curImage));
        m_outLabel.setPixmap(pixmap.scaled(m_curImage.width()*m_curScale, m_curImage.height()*m_curScale,Qt::KeepAspectRatio));
}

void SImageView::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::MiddleButton)
    {
        m_curScale = 1.0f;
        QPixmap pixmap(QPixmap::fromImage(m_curImage));
        m_outLabel.setPixmap(pixmap);
    }
}

