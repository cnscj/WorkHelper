#include "scoordinatemeasure.h"
#include "ui_scoordinatemeasure.h"

SCoordinateMeasure::SCoordinateMeasure(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SCoordinateMeasure)
{
    ui->setupUi(this);
    ui->fileListWidget->setDragTitleMode(SDragListWidget::DropItemTextMode::FileName);

    connect(ui->fileListWidget, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)), this, SLOT(showToImage(QListWidgetItem *)));
    connect(ui->scrollAreaWidgetContents, SIGNAL(position(SImgInfo)), this, SLOT(showImgInfo(SImgInfo)));



    ui->scrollAreaWidgetContents->setBackground(QColor(0,255,255));
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
    ui->scrollAreaWidgetContents->showImage(url.toLocalFile());
}


void SCoordinateMeasure::showImgInfo(SImgInfo info)
{
    QString str = QString("坐标:(%1,%2)").arg(info.x).arg(info.y);
    ui->lineEdit->setText(str);
}
