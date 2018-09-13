#include "Component/UI/SImageDrawWidget.h"
#include "Component/SDrawTool.h"
SImageDrawWidget::SImageDrawWidget(QWidget *parent)
: SImageView(parent)
{
    m_pDrawTool = new SDrawTool();
}

SImageDrawWidget::~SImageDrawWidget()
{
    delete m_pDrawTool;
}
