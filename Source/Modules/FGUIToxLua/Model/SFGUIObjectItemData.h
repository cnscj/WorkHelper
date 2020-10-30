#ifndef SFGUIOBJECTITEMDATA_H
#define SFGUIOBJECTITEMDATA_H
#include <QString>

class SFGUIObjectItemData
{
public:
    enum class ECategory{
        Component,
        Controller,
        Transition,
    };
public:
    int index;
    bool isDefaultName;
    ECategory category;
    QString name;
    QString type;
    QString oriType;
    QString desc;
public:
    SFGUIObjectItemData();
};

#endif // SFGUIOBJECTITEMDATA_H
