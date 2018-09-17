#ifndef SScrollAreaContentWidget_H
#define SScrollAreaContentWidget_H

#include "Component/UI/SImageDrawWidget.h"
#include "simginfo.h"
class SScrollAreaContentWidget : public SImageDrawWidget
{
    Q_OBJECT
public:
    explicit SScrollAreaContentWidget(QWidget *parent = 0);
    ~SScrollAreaContentWidget();
signals:
    void position(SImgInfo);
protected:

    virtual void paintEvent(QPaintEvent *e);
    virtual void enterEvent(QEvent *e);             //鼠标进入
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void leaveEvent(QEvent *e);             //鼠标离开
private:
    QPoint m_curPoint;
};

#endif // SScrollAreaContentWidget_H
