#ifndef SFGUIOBJECTITEM_H
#define SFGUIOBJECTITEM_H

#include <QWidget>
#include "../Model/SFGUIObjectItemData.h"
namespace Ui {
class SFGUIObjectItem;
}

class SFGUIObjectItem : public QWidget
{
    Q_OBJECT
public:
    explicit SFGUIObjectItem(QWidget *parent = 0);
    ~SFGUIObjectItem();
public:
    void setState(const SFGUIObjectItemData &data,int pos);

    void setData(const SFGUIObjectItemData &data);
    const SFGUIObjectItemData &getData();

    QString getPlaceholderString(const QString &prefix);
    QString getOutStringByName(const QString &prefix);
    QString getOutStringByIndex(const QString &prefix);

    void setEnabled(bool isEnable);
    bool isEnabled();
private:
    Ui::SFGUIObjectItem *ui;
    SFGUIObjectItemData m_data;
};

#endif // SFGUIOBJECTITEM_H
