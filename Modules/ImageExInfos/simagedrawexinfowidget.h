#ifndef SIMAGEDRAWEXINFOWIDGET_H
#define SIMAGEDRAWEXINFOWIDGET_H

#include "Component/UI/SImageDrawWidget.h"
class SImageDrawExInfoWidget : public SImageDrawWidget
{
    Q_OBJECT
public:
    explicit SImageDrawExInfoWidget(QWidget *parent = 0);
    ~SImageDrawExInfoWidget();
protected:
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void mouseReleaseEvent(QMouseEvent *e);
};

#endif // SIMAGEDRAWEXINFOWIDGET_H
