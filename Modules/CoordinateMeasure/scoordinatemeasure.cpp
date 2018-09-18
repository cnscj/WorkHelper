#include "scoordinatemeasure.h"
#include "ui_scoordinatemeasure.h"
#include "Util/SColorUtil.h"
SCoordinateMeasure::SCoordinateMeasure(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SCoordinateMeasure)
{
    ui->setupUi(this);
    ui->fileListWidget->setDragTitleMode(SDragListWidget::DropItemTextMode::FileName);

    connect(ui->fileListWidget, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)), this, SLOT(showToImage(QListWidgetItem *)));
    connect(ui->scrollAreaWidgetContents, SIGNAL(postInfo(SImgInfo &)), this, SLOT(showImgInfo(SImgInfo &)));



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


void SCoordinateMeasure::showImgInfo(SImgInfo &info)
{
    QColor pixel(info.pixel);
    QString str = QString("像素坐标:(%1,%2),原始宽度:(%3,%4),当前像素:<font color='%5'>■</font>(%6)\r\n,鼠标位置:(%7,%8),缩放倍率:%9f,当前宽度(%10,%11)")
               .arg(info.pixelX)
               .arg(info.pixelY)
               .arg(info.width)
               .arg(info.height)
               .arg(SColorUtil::makeColorString(pixel,"HEX"))
               .arg(SColorUtil::makeColorString(pixel,"HEX"))
               .arg(info.mouseX)
               .arg(info.mouseY)
               .arg(QString::number(info.scale,'f',2))
               .arg((int)(info.width * info.scale))
               .arg((int)(info.height * info.scale));
    ui->outInfo->setText(str);
}
