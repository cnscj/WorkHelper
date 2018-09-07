#ifndef SDRAGLISTWIDGET_H
#define SDRAGLISTWIDGET_H
#include <QtGui>
#include <QListWidget>
#include <QApplication>

class SDragListWidget: public QListWidget
{
    Q_OBJECT
public:
    enum class DargTitleMode
    {
        URL,
        FilePath,
        BaseName,
        FileName,
    };

public:
    explicit SDragListWidget(QWidget *parent);
    ~SDragListWidget();
public:
    void setDragTitleMode(DargTitleMode mode);
    DargTitleMode getDragTitleMode();

    QUrl *getUrl(QUrl *out,QListWidgetItem *item=nullptr);
    QList<QUrl> *getUrls(QList<QUrl> *out);

protected:
    //重写下面两个函数来完成从该部件中拖拽出去的操作.
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    //重写下面三个函数来完成接受外来拖拽的操作.
    void dragEnterEvent(QDragEnterEvent *event);        //拖入时
    void dragMoveEvent(QDragMoveEvent *event);          //拖动时
    void dropEvent(QDropEvent *event);                  //拖完时

signals:
    void drop(QDropEvent *event);                       //拖完时
private:
    QPoint                  m_dragPoint;        //记录拖拽的起点.
    QListWidgetItem         *m_dragItem;        //记录被拖拽的项.

    QMap<QString,QUrl>      m_urlsMap;          //记录完整的URLs路劲
    DargTitleMode           m_dragTitleMode;    //拖拽进行的标题显示模式
};

#endif // SDRAGLISTWIDGET_H
