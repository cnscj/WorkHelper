#ifndef SIMAGEDRAWCOORWIDGET_H
#define SIMAGEDRAWCOORWIDGET_H

#include "Component/UI/SImageDrawWidget.h"
class SImageDrawCoorWidget : public SImageDrawWidget
{
    Q_OBJECT
public:
    explicit SImageDrawCoorWidget(QWidget *parent = 0);
    ~SImageDrawCoorWidget();
protected:
    virtual void mouseMoveEvent(QMouseEvent *e);
};

#endif // SIMAGEDRAWCOORWIDGET_H
