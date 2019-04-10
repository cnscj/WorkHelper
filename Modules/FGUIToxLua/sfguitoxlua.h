#ifndef SFGUITOXLUA_H
#define SFGUITOXLUA_H

#include <QLinkedList>
#include <QWidget>
#include "Model/SFGUIObjectItemData.h"
namespace Ui {
class SFGUIToxLua;
}

class SFGUIToxLua : public QWidget
{
    Q_OBJECT

public:
    explicit SFGUIToxLua(QWidget *parent = 0);
    ~SFGUIToxLua();
protected:
    void praseXml();
    void setListProvider(const QLinkedList<SFGUIObjectItemData> &list);
    void clearAllObjects();

    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
protected slots:
    void openFile();
    void refreshSlot();
    void produceSlot();

private:
    Ui::SFGUIToxLua *ui;
    QLinkedList<SFGUIObjectItemData> m_data;
};

#endif // SFGUITOXLUA_H
