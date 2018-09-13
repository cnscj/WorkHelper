#ifndef SIMAGEDRAWWIDGET_H
#define SIMAGEDRAWWIDGET_H

#include "SImageView.h"

class SDrawTool;

class SImageDrawWidget : public SImageView
{
    Q_OBJECT
public:
    explicit SImageDrawWidget(QWidget *parent=nullptr);
    ~SImageDrawWidget();
private:
    SDrawTool   *m_pDrawTool;           //辅助的绘制工具
};

#endif // SIMAGEDRAWWIDGET_H
