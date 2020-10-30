#ifndef SMarkPoint_H
#define SMarkPoint_H

#include <QPoint>
#include <QPainter>
class SMarkPoint
{
public:
    SMarkPoint(const QPoint &p,int size = 2,Qt::GlobalColor color = Qt::black);
    ~SMarkPoint();

    void setMarkPos(const QPoint &p);
    const QPoint &getMarkPos();

    void setMarkSize(int size);
    const int &getMarkSize();

    void setMarkColor(Qt::GlobalColor color);
    const Qt::GlobalColor &getMarkColor();

    void draw(QPainter *);
private:
    QPoint m_MarkPos;
    int m_MarkSize;
    Qt::GlobalColor m_MarkColor;

};

#endif // SMarkPoint_H
