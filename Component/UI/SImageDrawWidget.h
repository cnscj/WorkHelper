#ifndef SIMAGEDRAWWIDGET_H
#define SIMAGEDRAWWIDGET_H

#include "SImageView.h"

class SImageDrawWidget : public SImageView
{
    Q_OBJECT
public:
    explicit SImageDrawWidget(QWidget *parent=nullptr);
    ~SImageDrawWidget();
};

#endif // SIMAGEDRAWWIDGET_H
