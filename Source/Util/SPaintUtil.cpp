#include "SPaintUtil.h"
#include <QPen>
#include <QBrush>
#include <QColor>

void SPaintUtil::drawPoint(QPainter &painter,const QPoint &p,int size,const QColor &color)
{
    auto oldBrush = painter.brush();
    auto newBrush = QBrush(color);
    painter.setBrush(newBrush);
    painter.drawEllipse(p,size,size);
    painter.setBrush(oldBrush);
}
void SPaintUtil::drawPoints(QPainter &painter,const QVector<QPoint> &points,const QSize &size,const QColor &color)
{
    auto oldBrush = painter.brush();
    auto newBrush = QBrush(color);
    painter.setBrush(newBrush);
    for(int i = 0; i<points.length(); i++)
    {
        painter.drawEllipse(points.at(i),size.width(),size.height());
        painter.drawPoint(points.at(i));
    }
    painter.setBrush(oldBrush);
}
void drawLine(QPainter &painter,const QPoint &a,const QPoint &b,int size,const QColor &color = QColor(Qt::red))
{
    auto oldPen = painter.pen();
    auto newPen = QPen(color,size);
    painter.setPen(newPen);
    {
        QLine line(a,b);
        painter.drawLine(line);
    }
    painter.setPen(oldPen);

}
void SPaintUtil::drawPolygon(QPainter &painter,const QVector<QPoint> &points,int size,const QColor &color)
{
    auto oldPen = painter.pen();
    auto newPen = QPen(color,size);
    painter.setPen(newPen);
    int n = points.length();
    for(int i = 0; i < n - 1; i++)
    {
        painter.drawLine(points.at(i),points.at(i+1));
    }
    if (n > 0) painter.drawLine(points.at(n-1),points.at(0));
    painter.setPen(oldPen);
}
void SPaintUtil::drawWidget(QPainter &painter,const QWidget &widget)
{
    auto oldPen = painter.pen();
    auto newPen = QPen(Qt::red);
    painter.setPen(newPen);
    painter.drawRect(QRect(widget.pos().x(),widget.pos().y(),widget.width(),widget.height()));
    painter.setPen(oldPen);
}
