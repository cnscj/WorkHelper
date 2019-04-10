#include "sfguiobjectitem.h"
#include "ui_sfguiobjectitem.h"

SFGUIObjectItem::SFGUIObjectItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SFGUIObjectItem)
{
    ui->setupUi(this);
}
void SFGUIObjectItem::setState(const SFGUIObjectItemData &data,int pos)
{
    Q_UNUSED(pos);
    setData(data);

}
void SFGUIObjectItem::setData(const SFGUIObjectItemData &data)
{
    m_data = data;

    ui->outRb->setChecked(true);
    ui->ObjLe->setText(QString("%1(\"%2\")").arg(m_data.name).arg(m_data.oriType));
}
const SFGUIObjectItemData &SFGUIObjectItem::getData()
{
    return m_data;
}

QString SFGUIObjectItem::getPlaceholderString(const QString &prefix)
{
    return QString("self.%1%2 = false").arg(prefix).arg(m_data.name);
}

QString SFGUIObjectItem::getOutStringByName(const QString &prefix)
{
    return QString("self.%1%2 = self._root:getChild(\"%3\", \"%4\")").arg(prefix).arg(m_data.name).arg(m_data.name).arg(m_data.type);
}

QString SFGUIObjectItem::getOutStringByIndex(const QString &prefix)
{
    return QString("self.%1%2 = self._root:getChildAt(%3, \"%4\")").arg(prefix).arg(m_data.name).arg(m_data.index).arg(m_data.type);
}

void SFGUIObjectItem::setEnabled(bool isEnable)
{
    ui->outRb->setChecked(isEnable);
}

bool SFGUIObjectItem::isEnabled()
{
    return ui->outRb->isChecked();
}

SFGUIObjectItem::~SFGUIObjectItem()
{
    delete ui;
}
