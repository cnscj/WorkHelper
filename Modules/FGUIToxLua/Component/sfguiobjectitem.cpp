#include "sfguiobjectitem.h"
#include "ui_sfguiobjectitem.h"

QString trans2Upper(const QString &ori,int length = 1)
{
    QString oneStr = ori.mid(0,length);
    QString seconeStr = ori.mid(length);
    return QString("%1%2").arg(oneStr.toUpper()).arg(seconeStr);
}

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

QString SFGUIObjectItem::getPlaceholderString(const OutputParams &params)
{
    return QString("%1%2 = false").
            arg(params.prefix).
            arg(params.isFirstUpper ? trans2Upper(m_data.name):m_data.name);
}

QString SFGUIObjectItem::getOutStringByName(const OutputParams &params)
{
    return QString("%1%2 = %3:getChild(\"%4\", \"%5\")").
            arg(params.prefix).
            arg(params.isFirstUpper ? trans2Upper(m_data.name):m_data.name).
            arg(params.parentName).
            arg(m_data.name).
            arg(m_data.type);
}

QString SFGUIObjectItem::getOutStringByIndex(const OutputParams &params)
{
    return QString("%1%2 = %3:getChildAt(%4, \"%5\")").
            arg(params.prefix).
            arg(params.isFirstUpper ? trans2Upper(m_data.name):m_data.name).
            arg(params.parentName).
            arg(m_data.index).
            arg(m_data.type);
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
