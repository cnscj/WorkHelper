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

protected:
    //重写下面两个函数来完成从该部件中拖拽出去的操作.
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

private:
    QPoint                              m_dragPoint;        //记录拖拽的起点.

    QListWidgetItem                     *m_dragItem;        //记录被拖拽的项.
};

#endif // SDragSortListWidget_H
