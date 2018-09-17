#include "SDragListWidget.h"

SDragListWidget::SDragListWidget(QWidget *parent)
    : QListWidget(parent),
      m_bDragSortEnabled(false)
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


void SDragListWidget::setDragSortEnabled(bool isEnabled)
{
    m_bDragSortEnabled = isEnabled;
}
bool SDragListWidget::getDragSortEnabled()
{
    return m_bDragSortEnabled;
}
////////////////////////////////
////////////////////////////////

//重写鼠标点击操作.
void SDragListWidget::mousePressEvent(QMouseEvent *event)
{
    if (m_bDragSortEnabled )
    {
        //确保左键拖拽.
        if (event->button() == Qt::LeftButton)
        {
            //先保存拖拽的起点.
            m_dragPoint = event->pos();
            //保留被拖拽的项.
            m_dragItem = this->itemAt(event->pos());
        }
    }

    //保留原QListWidget部件的鼠标点击操作.
    QListWidget::mousePressEvent(event);
}

void SDragListWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (m_bDragSortEnabled )
    {
        //确保按住左键移动.
        if (event->buttons() & Qt::LeftButton)
        {
            QPoint temp = event->pos() - m_dragPoint;
            //只有这个长度大于默认的距离,才会被系统认为是形成拖拽的操作.
            if (temp.manhattanLength() > QApplication::startDragDistance())
            {
                auto curItem = this->itemAt(event->pos());//找到当前鼠标位置在部件中的项.
                int curRow = this->row(curItem);
                int dragRow =  this->row(m_dragItem);

                this->swapItem(curRow,dragRow);
            }
        }
    }
    QListWidget::mouseMoveEvent(event);
}

void SDragListWidget::mouseReleaseEvent(QMouseEvent * event)
{
//    if (m_bDragSortEnabled )
//    {
//        if (event->button() == Qt::LeftButton)
//        {
//

//        }
//        setCursor(Qt::ArrowCursor);
//    }

    QListWidget::mouseReleaseEvent(event);
}

////
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
            if (!item)
              this->addUrlItem(it);
            else
              this->insertUrlItem(it,this->row(item));
        }
    }

    emit drop(event);
}

void SDragListWidget::keyPressEvent(QKeyEvent *ev)
{
    if (ev->key() == Qt::Key_Delete || ev->key() == Qt::Key_Backspace)
    {
        QList<QListWidgetItem *> list = this->selectedItems();
        removeUrlItems(list);
        ev->accept();
        return;
    }

    QListWidget::keyPressEvent(ev);
}

void SDragListWidget::addUrlItem(QUrl url)
{
    QString itemName = getUrlItemText(url);
    QListWidgetItem *widgetItem = new QListWidgetItem(itemName);
    this->addItem(widgetItem);
    m_urlsMap.insert(widgetItem,url);

}
void SDragListWidget::addUrlItems(QList<QUrl> &urls)
{
    for(const auto it : urls)
    {
       addUrlItem(it);
    }
}
void SDragListWidget::insertUrlItem(QUrl url,int pos)
{
    QString itemName = getUrlItemText(url);
    QListWidgetItem *widgetItem = new QListWidgetItem(itemName);
    this->insertItem(pos,widgetItem);
    m_urlsMap.insert(widgetItem,url);

}
void SDragListWidget::removeUrlItem(QListWidgetItem *item)
{
    QListWidget::removeItemWidget(item);
    m_urlsMap.remove(item);
    delete item;
}


void SDragListWidget::removeUrlItems(QList<QListWidgetItem *> &items)
{
    for(const auto it : items)
    {
        QListWidget::removeItemWidget(it);
        m_urlsMap.remove(it);
        delete it;
    }
}

void SDragListWidget::removeAllUrlItems()
{
    QList<QListWidgetItem*> allItems;
    for (int i = 0; i < this->count(); i++)
    {
        auto item = this->item(i);
        allItems.push_back(item);
    }
    this->removeUrlItems(allItems);
}

QUrl *SDragListWidget::getUrl(QUrl *pOut,const QListWidgetItem *item)
{
    if ( !pOut ) return nullptr;

    QListWidgetItem *itemWidget;
    if ( item ) itemWidget = (QListWidgetItem *)item;
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

void SDragListWidget::addUrl(QUrl url,QListWidgetItem *item)
{
    if ( !item ) return ;

    this->addItem(item);
    m_urlsMap.insert(item,url);
}

void SDragListWidget::insertUrl(QUrl url,QListWidgetItem *item,int pos)
{
    if ( !item ) return ;

    this->insertItem(pos,item);
    m_urlsMap.insert(item,url);
}

QList<QUrl> *SDragListWidget::getUrls(QList<QUrl> *pOut,const QList<QListWidgetItem*> *items)
{
    if ( !pOut ) return nullptr;

    QList<QListWidgetItem*> temp;
    QList<QListWidgetItem*> *pList = &temp;
    if ( items ) pList = (QList<QListWidgetItem*> *)items;
    else temp = this->selectedItems();

    for(auto it : *pList)
    {
        auto pair = m_urlsMap.find(it);
        if (pair != m_urlsMap.end())
        {
            pOut->push_back(pair.value());
        }

    }

    return pOut;
}

QList<QUrl> *SDragListWidget::getAllUrls(QList<QUrl> *out)
{
    if ( !out ) return nullptr;

    QList<QListWidgetItem*> allItems;
    for (int i = 0; i < this->count(); i++)
    {
        auto item = this->item(i);
        allItems.push_back(item);
    }

    return this->getUrls(out,&allItems);
}
//
QString SDragListWidget::getUrlItemText(QUrl url)
{
    QString itemName;
    switch(m_dropItemTextMode)
    {
        case DropItemTextMode::URL:
        {
            itemName = url.toString();
        }break;
        case DropItemTextMode::FilePath:
        {
             itemName = url.toLocalFile();//将第一个URL作为本地文件路径
        }break;
        case DropItemTextMode::BaseName:
        {
            QFileInfo fileInfo(url.toLocalFile());
            itemName = fileInfo.baseName();


        }break;
        case DropItemTextMode::FileName:
        {
            QFileInfo fileInfo(url.toLocalFile());
            itemName = fileInfo.fileName();

        }break;
        default:
        {
            itemName = url.toString();
        }break;
    };
    return itemName;
}

///////////////////
//////////////////
void SDragListWidget::swapItem(int aRow,int bRow)
{
    if (aRow != bRow)
    {
        if (aRow != -1 && bRow != -1)
        {
            int max = aRow > bRow ? aRow : bRow;
            int min = aRow < bRow ? aRow : bRow;
            //移除item后,row会发生变化
            auto maxItem = this->item(max);
            auto minItem = this->item(min);

            this->takeItem(min);
            this->removeItemWidget(minItem);
            this->insertItem(max,minItem);

            this->takeItem(max-1);
            this->removeItemWidget(maxItem);
            this->insertItem(min,maxItem);

            emit swapFinished();
        }
    }
}
