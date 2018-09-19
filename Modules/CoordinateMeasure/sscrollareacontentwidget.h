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
    void postInfo(SImgInfo &);
protected:

    virtual void paintEvent(QPaintEvent *e);
    virtual void enterEvent(QEvent *e);             //鼠标进入
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void leaveEvent(QEvent *e);             //鼠标离开
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseReleaseEvent(QMouseEvent *e);

    //重写键盘监听消息
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void keyReleaseEvent(QKeyEvent *e);
    virtual void wheelEvent(QWheelEvent *e);           //滚轮事件

private:
    QPoint          m_curPoint;
    QRgb            m_curRgb;
    SImgInfo        m_curInfo;

    bool            m_isWantScalel;
    bool            m_isCanMove;
    bool            m_isWantResetAnchorPoint;
};

#endif // SScrollAreaContentWidget_H
