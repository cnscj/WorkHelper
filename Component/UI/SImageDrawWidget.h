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
    void drawPoint(const QPoint &p);
protected:
    virtual void paintEvent(QPaintEvent *);
private:
    SDrawTool   m_drawTool;           //辅助的绘制工具
};

#endif // SIMAGEDRAWWIDGET_H
