#ifndef SDragKeyListWidget_H
#define SDragKeyListWidget_H

#include "Component/UI/SDragListWidget.h"
class SDragKeyListWidget: public SDragListWidget
{
        Q_OBJECT
public:
    explicit SDragKeyListWidget(QWidget *parent=nullptr);
    ~SDragKeyListWidget();
public slots:
    void setSwapRow(int row);

protected:
    //重写键盘监听消息
    virtual void keyPressEvent(QKeyEvent * ev);
private:
    int m_swapRow;    //记录当前src的row
};

#endif // SDragKeyListWidget_H
