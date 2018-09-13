#include "sfilesreplace.h"
#include "ui_sfilesreplace.h"

SFilesReplace::SFilesReplace(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SFilesReplace)
{
    ui->setupUi(this);

    ui->srcFileList->setDragTitleMode(SDragListWidget::DropItemTextMode::FilePath);
    ui->destFileList->setDragTitleMode(SDragListWidget::DropItemTextMode::FilePath);

    connect(ui->srcFileList, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)), this, SLOT(showToSrcImage(QListWidgetItem *)));
    connect(ui->destFileList, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)), this, SLOT(showToDestImage(QListWidgetItem *)));
    connect(ui->srcFileList, SIGNAL(currentRowChanged(int)), this, SLOT(srcListRowChanged(int)));


    connect(ui->srcFileList, SIGNAL(currentRowChanged(int)), ui->destFileList, SLOT(setSwapRow(int)));
    connect(ui->destFileList, SIGNAL(swapFinished()), ui->srcFileList, SLOT(nextItem()));
}

SFilesReplace::~SFilesReplace()
{
    delete ui;
}


void SFilesReplace::showToSrcImage(QListWidgetItem *item)
{
    if (!item) return ;

    QUrl url;
    ui->srcFileList->getUrl(&url,item);
    ui->srcImageView->showImage(url.toLocalFile());
}

void SFilesReplace::showToDestImage(QListWidgetItem *item)
{
    if (!item) return ;

    QUrl url;
    ui->destFileList->getUrl(&url,item);
    ui->destImageView->showImage(url.toLocalFile());
}

void SFilesReplace::srcListRowChanged(int row)
{
    ui->destFileList->setCurrentRow(row);
}
