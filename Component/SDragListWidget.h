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

    QUrl *getUrl(QUrl *out,const QListWidgetItem *item=nullptr);
    QList<QUrl> *getUrls(QList<QUrl> *out);

    void removeItemWidgetList(const QList<QListWidgetItem *> &items);
protected:
    //重写下面两个函数来完成从该部件中拖拽出去的操作.
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    //重写下面三个函数来完成接受外来拖拽的操作.
    virtual void dragEnterEvent(QDragEnterEvent *event);        //拖入时
    virtual void dragMoveEvent(QDragMoveEvent *event);          //拖动时
    virtual void dropEvent(QDropEvent *event);                  //拖完时
    //重写键盘监听消息
    virtual void keyPressEvent(QKeyEvent * ev);
signals:
    void drop(QDropEvent *event);                       //拖完时
private:
    QPoint                              m_dragPoint;        //记录拖拽的起点.
    QListWidgetItem                     *m_dragItem;        //记录被拖拽的项.

    QMap<QListWidgetItem *,QUrl>        m_urlsMap;          //记录完整的URLs路劲
    DropItemTextMode                    m_dropItemTextMode;    //拖拽进行的标题显示模式
};

#endif // SDRAGLISTWIDGET_H
