#ifndef SU9INJECTITEM_H
#define SU9INJECTITEM_H

#include <QWidget>

namespace Ui {
class SU9InjectItem;
}

class SU9InjectItem : public QWidget
{
    Q_OBJECT

public:
    explicit SU9InjectItem(QWidget *parent = 0);
    ~SU9InjectItem();
public:
    void setState(void *data,int index);
    bool isSelected();
    void setSelected(bool val);
private:
    Ui::SU9InjectItem *ui;
};

#endif // SU9INJECTITEM_H
