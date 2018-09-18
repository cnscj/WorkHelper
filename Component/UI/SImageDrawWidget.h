#ifndef SIMAGEDRAWWIDGET_H
#define SIMAGEDRAWWIDGET_H

#include "SImageWidget.h"
class SDrawTool;

class SImageDrawWidget : public SImageWidget
{
    Q_OBJECT
public:
    explicit SImageDrawWidget(QWidget *parent=nullptr);
    ~SImageDrawWidget();
protected:
    virtual void paintEvent(QPaintEvent *);

protected:

};

#endif // SIMAGEDRAWWIDGET_H
