#include "Modules/FileNameFactor/sfilenamefactor.h"
#include "ui_sfilenamefactor.h"

SFileNameFactor::SFileNameFactor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SFileNameFactor)
{
    ui->setupUi(this);
    ui->filePathsList->setDragTitleMode(SDragListWidget::DropItemTextMode::FilePath);


    connect(ui->produceBtn, SIGNAL(clicked()), this, SLOT(showToText()));
}

SFileNameFactor::~SFileNameFactor()
{
    delete ui;
}


void SFileNameFactor::showToText()
{
    QString out = "";
    QList<QUrl> list;
    ui->filePathsList->getUrls(&list);

    for(auto it : list)
    {
        QFileInfo fileInfo(it.toLocalFile());
        QString baseName = fileInfo.baseName();
        QString filePath = fileInfo.filePath();
        out += QString("%1 = \"%2\" ,\n").arg(baseName).arg(filePath);

    }
    ui->outPutText->setText(out);
}
