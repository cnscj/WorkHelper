#include "Component/SDragListWidget.h"

SDragListWidget::SDragListWidget(QWidget *parent)
    : QListWidget(parent)
{
    //设置QListWidget接受拖拽.
    this->setAcceptDrops(true);

    m_dragTitleMode = DargTitleMode::URL;
}

SDragListWidget::~SDragListWidget()
{

}
void SDragListWidget::setDragTitleMode(SDragListWidget::DargTitleMode mode)
{
    m_dragTitleMode = mode;
}

SDragListWidget::DargTitleMode SDragListWidget::getDragTitleMode()
{
    return m_dragTitleMode;
}

////////////////////////////////
////////////////////////////////
//重写鼠标点击操作.
void SDragListWidget::mousePressEvent(QMouseEvent *event)
{

//    //确保左键拖拽.
//    if (event->button() == Qt::LeftButton)
//    {
//        //先保存拖拽的起点.
//        m_dragPoint = event->pos();
//        //保留被拖拽的项.
//        m_dragItem = this->itemAt(event->pos());
//    }
//    //保留原QListWidget部件的鼠标点击操作.
    QListWidget::mousePressEvent(event);
}

void SDragListWidget::mouseMoveEvent(QMouseEvent *event)
{
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
    QListWidget::mouseMoveEvent(event);
}

void SDragListWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasUrls())//数据是否包含URls
    {
        event->acceptProposedAction();//接收动作
        //若不添加此函数，则外部文件无法添加到窗体中
    }
    else
    {
        event->ignore();//忽略事件
    }


}
void SDragListWidget::dragMoveEvent(QDragMoveEvent *event)
{
    event->setDropAction(Qt::LinkAction);       //以链接的方式把文件拖放到此
    event->accept();
}
//当拖拽项被放下时的操作.
void SDragListWidget::dropEvent(QDropEvent *event)
{

    const QMimeData *mimeData = event->mimeData();//获取mimie数据
    if(mimeData->hasUrls())
    {
        QList<QUrl> urlList = mimeData->urls();//获取url列表
        auto item = this->itemAt(event->pos());//找到当前鼠标位置在部件中的项.
        for(const auto it:urlList)
        {
            QString itemName;
            switch(m_dragTitleMode)
            {
                case DargTitleMode::URL:
                {
                    itemName = it.toString();
                }break;
                case DargTitleMode::FilePath:
                {
                     itemName = it.toLocalFile();//将第一个URL作为本地文件路径
                }break;
                case DargTitleMode::BaseName:
                {
                    QFileInfo fileInfo(it.toLocalFile());
                    itemName = fileInfo.baseName();


                }break;
                case DargTitleMode::FileName:
                {
                    QFileInfo fileInfo(it.toLocalFile());
                    itemName = fileInfo.fileName();


                }break;
            };

            if (!item)
              this->addItem(itemName);
            else
              this->insertItem(this->row(item),itemName);

            m_urlsMap.insert(itemName,it);
        }
    }

    emit drop(event);
}

QUrl *SDragListWidget::getUrl(QUrl *pOut,QListWidgetItem *item)
{
    if ( !pOut ) return nullptr;

    QListWidgetItem *itemWidget;
    if ( !item ) itemWidget = item;
    else itemWidget = this->currentItem();

    if (itemWidget)
    {
        QString key = itemWidget->text();
        auto pair = m_urlsMap.find(key);
        if (pair != m_urlsMap.end())
        {
            *pOut = pair.value();
        }

        return pOut;
    }
    return nullptr;
}

QUrl *SDragListWidget::getUrl(QUrl *pOut,QString key)
{
    if ( !pOut ) return nullptr;

    auto pair = m_urlsMap.find(key);
    if (pair != m_urlsMap.end())
    {
        *pOut = pair.value();
    }

    return pOut;
}

QList<QUrl> *SDragListWidget::getUrls(QList<QUrl> *pOut)
{
    if ( !pOut ) return nullptr;

    QList<QListWidgetItem*> pList = this->selectedItems();

    for(auto it : pList)
    {
        QString key = it->text();
        auto pair = m_urlsMap.find(key);
        if (pair != m_urlsMap.end())
        {
            pOut->push_back(pair.value());
        }

    }

    return pOut;
}

