#ifndef SPAINTUTIL_H
#define SPAINTUTIL_H

#include <QPoint>
#include <QPainter>
#include <QVector>
#include <QWidget>
namespace SPaintUtil
{
    void drawPoint(QPainter &painter,const QPoint &p,int size = 1,const QColor &color = QColor(Qt::red));
    void drawPoints(QPainter &painter,const QVector<QPoint> &points,const QSize &size = QSize(1,1),const QColor &color = QColor(Qt::red));
    void drawPolygon(QPainter &painter,const QVector<QPoint> &points,const QSize &size = QSize(1,1),const QColor &color = QColor(Qt::red));
    void drawWidget(QPainter &painter,const QWidget &widget);
}

#endif // SPAINTUTIL_H
