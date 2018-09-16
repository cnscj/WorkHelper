#ifndef SIMAGEDRAWWIDGET_H
#define SIMAGEDRAWWIDGET_H

#include "SImageView.h"
#include "../SDrawTool.h"
class SDrawTool;

class SImageDrawWidget : public SImageView
{
    Q_OBJECT
public:
    explicit SImageDrawWidget(QWidget *parent=nullptr);
    ~SImageDrawWidget();
public:
    void addPoint(const QPoint &p);
protected:
    void drawPoints(QPainter &painter);
    void drawPolygon(QPainter &painter);
protected:
    virtual void paintEvent(QPaintEvent *);
private:
    SDrawTool     m_drawTool;
};

#endif // SIMAGEDRAWWIDGET_H
