#include "Component/SDragListWidget.h"

SDragListWidget::SDragListWidget(QWidget *parent)
    : QListWidget(parent)
{
    //设置QListWidget接受拖拽.
    this->setAcceptDrops(true);

    m_dropItemTextMode = DropItemTextMode::URL;
}

SDragListWidget::~SDragListWidget()
{

}
void SDragListWidget::setDragTitleMode(SDragListWidget::DropItemTextMode mode)
{
    m_dropItemTextMode = mode;
}

SDragListWidget::DropItemTextMode SDragListWidget::getDragTitleMode()
{
    return m_dropItemTextMode;
}

////////////////////////////////
////////////////////////////////

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
            switch(m_dropItemTextMode)
            {
                case DropItemTextMode::URL:
                {
                    itemName = it.toString();
                }break;
                case DropItemTextMode::FilePath:
                {
                     itemName = it.toLocalFile();//将第一个URL作为本地文件路径
                }break;
                case DropItemTextMode::BaseName:
                {
                    QFileInfo fileInfo(it.toLocalFile());
                    itemName = fileInfo.baseName();


                }break;
                case DropItemTextMode::FileName:
                {
                    QFileInfo fileInfo(it.toLocalFile());
                    itemName = fileInfo.fileName();


                }break;
            };

            QListWidgetItem *widgetItem = new QListWidgetItem(itemName);
            if (!item)
              this->addItem(widgetItem);
            else
              this->insertItem(this->row(item),widgetItem);

            m_urlsMap.insert(widgetItem,it);
        }
    }

    emit drop(event);
}

void SDragListWidget::keyPressEvent(QKeyEvent * ev)
{
    if (ev->key() == Qt::Key_Delete || ev->key() == Qt::Key_Backspace)
    {
        QList<QListWidgetItem *> list = this->selectedItems();
        removeItemWidgetList(list);
        ev->accept();
        return;
    }

    QListWidget::keyPressEvent(ev);
}

void SDragListWidget::removeItemWidgetList(const QList<QListWidgetItem *> &items)
{
    for(const auto it : items)
    {
        QListWidget::removeItemWidget(it);
        m_urlsMap.remove(it);
        delete it;
    }
}


QUrl *SDragListWidget::getUrl(QUrl *pOut,const QListWidgetItem *item)
{
    if ( !pOut ) return nullptr;

    QListWidgetItem *itemWidget;
    if ( !item ) itemWidget = (QListWidgetItem *)item;
    else itemWidget = this->currentItem();

    if (itemWidget)
    {
        auto pair = m_urlsMap.find(itemWidget);
        if (pair != m_urlsMap.end())
        {
            *pOut = pair.value();
        }
    }
    return pOut;
}

QList<QUrl> *SDragListWidget::getUrls(QList<QUrl> *pOut)
{
    if ( !pOut ) return nullptr;

    QList<QListWidgetItem*> pList = this->selectedItems();

    for(auto it : pList)
    {
        auto pair = m_urlsMap.find(it);
        if (pair != m_urlsMap.end())
        {
            pOut->push_back(pair.value());
        }

    }

    return pOut;
}

