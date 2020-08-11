#include "SU9InjectItem.h"
#include "ui_su9injectitem.h"

SU9InjectItem::SU9InjectItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SU9InjectItem)
{
    ui->setupUi(this);
}

void SU9InjectItem::setState(void *data,int index)
{
    QString *fileName = (QString *)data;
    ui->objLe->setText(*fileName);
}

bool SU9InjectItem::isSelected()
{
    return ui->outRb->isChecked();
}

void SU9InjectItem::setSelected(bool val)
{
    ui->outRb->setChecked(val);
}

SU9InjectItem::~SU9InjectItem()
{
    delete ui;
}
