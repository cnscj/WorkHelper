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
    //确保左键拖拽.
    if (event->button() == Qt::LeftButton)
    {
        //先保存拖拽的起点.
        m_dragPoint = event->pos();
        //保留被拖拽的项.
        m_dragItem = this->itemAt(event->pos());
    }
    //保留原QListWidget部件的鼠标点击操作.
    SDragListWidget::mousePressEvent(event);
}

void SDragMoveListWidget::mouseMoveEvent(QMouseEvent *event)
{
    //确保按住左键移动.
    if (event->buttons() & Qt::LeftButton)
    {
        QPoint temp = event->pos() - m_dragPoint;
        //只有这个长度大于默认的距离,才会被系统认为是形成拖拽的操作.
        if (temp.manhattanLength() > QApplication::startDragDistance())
        {
            QDrag *drag = new QDrag(this);
            QMimeData *mimeData = new QMimeData;
            mimeData->setText(m_dragItem->text());
            drag->setMimeData(mimeData);
            auto action = drag->exec(Qt::MoveAction);

//            if (action == Qt::MoveAction)
//            {
//                //当成功拖拽后，删除拖拽项.
////                auto i = this->takeItem(this->row(m_dragItem));
////                delete i;
//            }
        }
    }
    SDragListWidget::mouseMoveEvent(event);
}


void SDragMoveListWidget::dragEnterEvent(QDragEnterEvent *event)
{
    SDragMoveListWidget *source = (SDragMoveListWidget *)((void *)(event->source()));
    if (source && source == this)
    {
        qDebug("自己的");
        auto item = this->itemAt(event->pos());//找到当前鼠标位置在部件中的项.
        //TODO:交换2项
//        auto i = this->takeItem(this->row(m_dragItem));
//        delete i;

        event->accept();
    }
    else
    {
        qDebug("从别的地方来的");
        SDragListWidget::dragEnterEvent(event);
    }
}
void SDragMoveListWidget::dragMoveEvent(QDragMoveEvent *event)
{
    SDragListWidget::dragMoveEvent(event);
}
void SDragMoveListWidget::dropEvent(QDropEvent *event)
{
    SDragListWidget::dropEvent(event);
}
