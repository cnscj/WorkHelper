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


    ui->scrollAreaWidgetContents->setAnchorPoint(QPointF(0.f,1.f));
    ui->scrollAreaWidgetContents->showAnchorPoint();

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
    ui->scrollAreaWidgetContents->setBackground(QColor(0,255,255));
    ui->scrollAreaWidgetContents->showImage(url.toLocalFile());
}


void SCoordinateMeasure::showImgInfo(SImgInfo &info)
{
    QColor pixel(info.pixel);
    QString str = QString("像素坐标:(%1,%2),原始尺寸:(%3,%4),当前像素:<font color='%5'>■</font>(%6)\r\n,鼠标位置:(%7,%8),缩放倍率:%9f,当前尺寸(%10,%11),锚点:(%12,%13)")
               .arg(info.pixelPos.x())
               .arg(info.pixelPos.y())
               .arg(info.size.width())
               .arg(info.size.height())
               .arg(SColorUtil::makeColorString(pixel,"HEX"))
               .arg(SColorUtil::makeColorString(pixel,"HEX"))
               .arg(info.mousePos.x())
               .arg(info.mousePos.y())
               .arg(QString::number(info.scale,'f',2))
               .arg((int)(info.size.width() * info.scale))
               .arg((int)(info.size.height() * info.scale))
               .arg(QString::number(info.anchorPoint.x(),'f',2))
               .arg(QString::number(info.anchorPoint.y(),'f',2));
    ui->outInfo->setText(str);
}
