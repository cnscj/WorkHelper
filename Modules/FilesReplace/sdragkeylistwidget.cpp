#include "Modules/FilesReplace/sdragkeylistwidget.h"

SDragKeyListWidget::SDragKeyListWidget(QWidget *parent)
    :SDragListWidget(parent),
    m_swapRow(-1)
{

}

SDragKeyListWidget::~SDragKeyListWidget()
{

}

void SDragKeyListWidget::keyPressEvent(QKeyEvent * ev)
{
    if (ev->key() == Qt::Key_Space)
    {
        //取得当前选择的项,然后在取得另一个ListWidget的项序号,按照这个序号交换
        if (m_swapRow != -1)    //-1表示左侧没有序号,无法排序
        {
            int curRow = this->currentRow();
            this->swapItem(curRow,m_swapRow);
            emit keySortFinished();
        }
        return;
    }

    SDragListWidget::keyPressEvent(ev);
}
///
void SDragKeyListWidget::setSwapRow(int row)
{
    m_swapRow = row;
}
