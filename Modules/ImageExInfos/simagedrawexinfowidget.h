#ifndef SIMAGEDRAWEXINFOWIDGET_H
#define SIMAGEDRAWEXINFOWIDGET_H

#include "Component/UI/SImageDrawWidget.h"
class SImageDrawExInfoWidget : public SImageDrawWidget
{
    Q_OBJECT
public:
    explicit SImageDrawExInfoWidget(QWidget *parent = 0);
    ~SImageDrawExInfoWidget();
public slots:
    void markEnabled(bool);
protected:
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void mouseReleaseEvent(QMouseEvent *e);
private:
    bool m_bIsCanMarkPoint;
};

#endif // SIMAGEDRAWEXINFOWIDGET_H
