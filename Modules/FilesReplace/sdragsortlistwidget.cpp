#include "Modules/FilesReplace/sdragsortlistwidget.h"

SDragSortListWidget::SDragSortListWidget(QWidget *parent)
    :SDragListWidget(parent)
{

}

SDragSortListWidget::~SDragSortListWidget()
{

}

//重写鼠标点击操作.
void SDragSortListWidget::mousePressEvent(QMouseEvent *event)
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

void SDragSortListWidget::mouseMoveEvent(QMouseEvent *event)
{
    //确保按住左键移动.
    if (event->buttons() & Qt::LeftButton)
    {
        QPoint temp = event->pos() - m_dragPoint;
        //只有这个长度大于默认的距离,才会被系统认为是形成拖拽的操作.
        if (temp.manhattanLength() > QApplication::startDragDistance())
        {
//            QDrag *drag = new QDrag(this);
//            QMimeData *mimeData = new QMimeData;
//            mimeData->setText(m_dragItem->text());
//            drag->setMimeData(mimeData);
//            auto action = drag->exec(Qt::MoveAction);

//            auto item = this->itemAt(event->pos());//找到当前鼠标位置在部件中的项.
        }
    }

    SDragListWidget::mouseMoveEvent(event);
}

void SDragSortListWidget::mouseReleaseEvent(QMouseEvent * event)
{
    if (event->button() == Qt::LeftButton)
    {
        //TODO:

    }
    setCursor(Qt::ArrowCursor);

    SDragListWidget::mouseReleaseEvent(event);
}

/////
void SDragSortListWidget::nextItem()
{
    this->setCurrentRow(this->currentRow()+1);
}

