#ifndef SPAINTUTIL_H
#define SPAINTUTIL_H

#include <QPoint>
#include <QPainter>
#include <QVector>

namespace SPaintUtil
{
    void drawPoint(QPainter &painter,QPoint &p);
    void drawPolygon(QPainter &painter,QVector<QPoint> &points);
}

#endif // SPAINTUTIL_H
