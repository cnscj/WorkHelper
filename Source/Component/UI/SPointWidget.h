#ifndef SPointWidget_H
#define SPointWidget_H

#include "SShapeWidget.h"
class SPointWidget : public SShapeWidget
{
    Q_OBJECT
public:
    explicit SPointWidget(QWidget *parent=nullptr);
    ~SPointWidget();
protected:
    virtual void paintEvent(QPaintEvent *e);
};

#endif // SPointWidget_H
