#include "Component/UI/SDragMoveListWidget.h"

SDragMoveListWidget::SDragMoveListWidget(QWidget *parent)
    :SDragListWidget(parent)
{

}

SDragMoveListWidget::~SDragMoveListWidget()
{

}

//重写鼠标点击操作.
void SDragMoveListWidget::mousePressEvent(QMouseEvent *event)
{
    //TODO:
    //确保左键拖拽.
//    if (event->button() == Qt::LeftButton)
//    {
//        //先保存拖拽的起点.
//        m_dragPoint = event->pos();
//        //保留被拖拽的项.
//        m_dragItem = this->itemAt(event->pos());
//    }
//    //保留原QListWidget部件的鼠标点击操作.
    SDragListWidget::mousePressEvent(event);
}

void SDragMoveListWidget::mouseMoveEvent(QMouseEvent *event)
{
    //TODO:
//    //确保按住左键移动.
//    if (event->buttons() & Qt::LeftButton)
//    {
//        QPoint temp = event->pos() - m_dragPoint;
//        //只有这个长度大于默认的距离,才会被系统认为是形成拖拽的操作.
//        if (temp.manhattanLength() > QApplication::startDragDistance())
//        {
//            QDrag *drag = new QDrag(this);
//            QMimeData *mimeData = new QMimeData;
//            mimeData->setText(m_dragItem->text());
//            drag->setMimeData(mimeData);
//            auto action = drag->exec(Qt::CopyAction | Qt::MoveAction);

//            if (action == (Qt::CopyAction) || (action == Qt::MoveAction))
//            {
//                //当成功拖拽后，删除拖拽项.
//                auto i = this->takeItem(this->row(m_dragItem));
//                delete i;
//            }
//        }
//    }
    SDragListWidget::mouseMoveEvent(event);
}
