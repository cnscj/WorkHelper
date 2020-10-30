#include "sdragsortlistwidget.h"

SDragSortListWidget::SDragSortListWidget(QWidget *parent)
    :SDragListWidget(parent)
{

}

SDragSortListWidget::~SDragSortListWidget()
{

}


/////
void SDragSortListWidget::nextItem()
{
    this->setCurrentRow(this->currentRow()+1);
}

