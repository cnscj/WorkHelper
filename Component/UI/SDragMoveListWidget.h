#ifndef SDRAGMOVELISTWIDGET_H
#define SDRAGMOVELISTWIDGET_H
#include "Component/UI/SDragListWidget.h"

class SDragMoveListWidget : public SDragListWidget
{
       Q_OBJECT
public:
    explicit SDragMoveListWidget(QWidget *parent=nullptr);
    ~SDragMoveListWidget();
protected:
    //重写下面两个函数来完成从该部件中拖拽出去的操作.
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);

    virtual void dragEnterEvent(QDragEnterEvent *event);        //拖入时
    virtual void dragMoveEvent(QDragMoveEvent *event);          //拖动时
    virtual void dropEvent(QDropEvent *event);                  //拖完时
private:
    QPoint                              m_dragPoint;        //记录拖拽的起点.
    QListWidgetItem                     *m_dragItem;        //记录被拖拽的项.
};

#endif // SDRAGMOVELISTWIDGET_H
