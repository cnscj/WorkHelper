#ifndef SIMAGEDRAWWIDGET_H
#define SIMAGEDRAWWIDGET_H

#include "SImageWidget.h"
class SDrawTool;

class SImageDrawWidget : public SImageWidget
{
    Q_OBJECT
public:
    enum class PaintType
    {
        None,
        Points,
        Polygon,
    };
public:
    explicit SImageDrawWidget(QWidget *parent=nullptr);
    ~SImageDrawWidget();
public:
    const QVector<QPoint> &getPaintPoints() const;
    void setPaintPoints(QVector<QPoint> &points);
    void addPaintPoint(const QPoint &p);

    PaintType getPaintType()const ;
    void setPaintType(const PaintType type);

    void showAnchorPoint();
    void hideAnchorPoint();

    void paint(QVector<QPoint> &points,const PaintType type);
    void clear();
protected:
    virtual void paintEvent(QPaintEvent *);
protected:
    QVector<QPoint>         m_curPoints;
    PaintType               m_curPaintType;
    bool                    m_isShowAnchorPoint;
};

#endif // SIMAGEDRAWWIDGET_H
