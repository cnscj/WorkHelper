#include "scoordinatemeasure.h"
#include "ui_scoordinatemeasure.h"

SCoordinateMeasure::SCoordinateMeasure(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SCoordinateMeasure)
{
    ui->setupUi(this);
    ui->fileListWidget->setDragTitleMode(SDragListWidget::DropItemTextMode::FileName);

    connect(ui->fileListWidget, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)), this, SLOT(showToImage(QListWidgetItem *)));
}

SCoordinateMeasure::~SCoordinateMeasure()
{
    delete ui;
}

void SCoordinateMeasure::showToImage(QListWidgetItem *item)
{
    if (!item) return ;

    QUrl url;
    ui->fileListWidget->getUrl(&url,item);
    ui->imageWidget->showImage(url.toLocalFile());
}
