#ifndef BEZIERTOOL_H
#define BEZIERTOOL_H

#include <QObject>
#include <QPainter>
#include <QVector>
#include <QRect>
#include "Base/SMarkPoint.h"

class SDrawTool : public QObject
{
      Q_OBJECT
public:
    SDrawTool();
    ~SDrawTool();

    void addPoint(const QPoint &p);
    void deletePoint(int index);
    SMarkPoint *getPoint(int index);
    int searchPoint(const QPoint &p,int r);
    void clearPoints();
    const QVector<SMarkPoint *> *getPoints();

    void drawPoints(QPainter *painter);
    void drawPolygon(QPainter *painter);
    void drawBezier(QPainter *painter);

    void selectPoint(int index);
    bool isSelectedPoint();
    void cancelPoint();
    int getSelectedPoint();

protected:
    void drawPoint(QPainter *painter, SMarkPoint *p);
    void drawLine(QPainter *painter, SMarkPoint *a,  SMarkPoint *b);
    void drawBezier3(QPainter *painter, SMarkPoint *start, SMarkPoint *pos1, SMarkPoint *pos2, SMarkPoint *end);
private:
    QVector<SMarkPoint *> m_Points;
    int m_selectedMark;
};

#endif // BEZIERTOOL_H
