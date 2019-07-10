#include "Modules/MainUi/smainwidget.h"
#include "ui_smainwidget.h"

#include <QSettings>
#include "Modules/uimodules.h"
static const QString SETTING_GROUP_NAME = "MainWidget";
SMainWidget::SMainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SMainWidget)
{
    ui->setupUi(this);

    int length = sizeof(MODULES)/sizeof(MODULE_INFOS);

    for(int i = 0;i<length;++i)
    {
        auto &info = MODULES[i];
        auto widget = info.createWidget();
        ui->tabWidget->insertTab(info.index, widget , info.title);
        m_moduleStack.push(widget);
    }
    QSettings setting;
    setting.beginGroup(SETTING_GROUP_NAME);
    int lastIndex = setting.value("lastIndex",0).toInt();
    ui->tabWidget->setCurrentIndex(lastIndex);

    connect(ui->tabWidget,&QTabWidget::tabBarClicked,this,&SMainWidget::enterWidget);
}

void SMainWidget::enterWidget(int index)
{
    QSettings setting;
    setting.beginGroup(SETTING_GROUP_NAME);
    setting.setValue("lastIndex",index);
}

SMainWidget::~SMainWidget()
{
    while(!m_moduleStack.isEmpty())
    {
        auto widget = m_moduleStack.top();
        delete widget;
        m_moduleStack.pop();
    }

    delete ui;
}
