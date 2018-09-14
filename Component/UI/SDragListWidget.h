#ifndef SDRAGLISTWIDGET_H
#define SDRAGLISTWIDGET_H
#include <QtGui>
#include <QListWidget>
#include <QApplication>

class SDragListWidget: public QListWidget
{
    Q_OBJECT
public:
    enum class DropItemTextMode
    {
        URL,
        FilePath,
        BaseName,
        FileName,
    };

public:
    explicit SDragListWidget(QWidget *parent=nullptr);
    ~SDragListWidget();
public:
    void setDragTitleMode(DropItemTextMode mode);
    DropItemTextMode getDragTitleMode();


    void addUrl(QUrl url,QListWidgetItem *item);
    void insertUrl(QUrl url,QListWidgetItem *item,int pos);
    QUrl *getUrl(QUrl *out,const QListWidgetItem *item=nullptr);
    QList<QUrl> *getUrls(QList<QUrl> *out,const QList<QListWidgetItem*> *items=nullptr);
    QList<QUrl> *getAllUrls(QList<QUrl> *out);

    void addUrlItem(QUrl url);
    void insertUrlItem(QUrl url,int pos);
    void addUrlItems(QList<QUrl> &urls);
    void removeUrlItem(QListWidgetItem *item);
    void removeUrlItems(QList<QListWidgetItem *> &items);
    void removeAllUrlItems();

    void setDragSortEnabled(bool isEnabled);
    bool getDragSortEnabled();
protected:
    void swapItem(int aRow,int bRow);
protected:
    //重写下面两个函数来完成拖拽排序
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

    //重写下面三个函数来完成接受外来拖拽的操作.
    virtual void dragEnterEvent(QDragEnterEvent *event);        //拖入时
    virtual void dragMoveEvent(QDragMoveEvent *event);          //拖动时
    virtual void dropEvent(QDropEvent *event);                  //拖完时
    //重写键盘监听消息
    virtual void keyPressEvent(QKeyEvent * ev);
private:
    QString getUrlItemText(QUrl);
signals:
    void drop(QDropEvent *event);                               //拖完时
    void swapFinished();                                        //排序完毕的信号
protected:
    QMap<QListWidgetItem *,QUrl>        m_urlsMap;              //记录完整的URLs路劲
    DropItemTextMode                    m_dropItemTextMode;     //拖拽进行的标题显示模式

    bool                                m_bDragSortEnabled;     //是否支持拖拽排序
    QPoint                              m_dragPoint;            //记录拖拽的起点.
    QListWidgetItem                     *m_dragItem;            //记录被拖拽的项.
};

#endif // SDRAGLISTWIDGET_H
