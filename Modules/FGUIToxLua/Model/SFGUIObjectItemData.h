#ifndef SFGUIOBJECTITEMDATA_H
#define SFGUIOBJECTITEMDATA_H
#include <QString>

class SFGUIObjectItemData
{
public:
    int index;
    bool isDefaultName;
    QString name;
    QString type;
    QString oriType;

public:
    SFGUIObjectItemData();
};

#endif // SFGUIOBJECTITEMDATA_H
