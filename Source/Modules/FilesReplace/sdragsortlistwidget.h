#ifndef SDragSortListWidget_H
#define SDragSortListWidget_H

#include "Component/UI/SDragListWidget.h"

class SDragSortListWidget: public SDragListWidget
{
    Q_OBJECT
public:
    explicit SDragSortListWidget(QWidget *parent=nullptr);
    ~SDragSortListWidget();

public slots:
    void nextItem();

};

#endif // SDragSortListWidget_H
