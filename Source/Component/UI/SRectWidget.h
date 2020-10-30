#ifndef SRECTWIDGET_H
#define SRECTWIDGET_H

#include "SShapeWidget.h"
class SRectWidget : public SShapeWidget
{
    Q_OBJECT
public:
    explicit SRectWidget(QWidget *parent=nullptr);
    ~SRectWidget();
protected:
    virtual void paintEvent(QPaintEvent *e);
};

#endif // SRECTWIDGET_H
