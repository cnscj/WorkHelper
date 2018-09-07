#include "Modules/MainUi/smainwidget.h"
#include "ui_SMainWidget.h"

#include "Modules/uimodules.h"

SMainWidget::SMainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SMainWidget)
{
    ui->setupUi(this);

    int length = sizeof(MODULES)/sizeof(MODULE_INFOS);

    for(int i =0;i<length;++i)
    {
        auto &info = MODULES[i];
        auto widget = info.createWidget();
        ui->tabWidget->insertTab(info.index, widget , info.title);
        m_moduleStack.push(widget);
    }

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
