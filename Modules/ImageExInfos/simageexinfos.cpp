#include "Modules/ImageExInfos/simageexinfos.h"
#include "ui_simageexinfos.h"

SImageExInfos::SImageExInfos(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SImageExInfos)
{
    ui->setupUi(this);
    ui->fileNamesList->setDragTitleMode(SDragListWidget::DropItemTextMode::FileName);

    connect(ui->produceBtn, SIGNAL(clicked()), this, SLOT(showToText()));
//    connect(ui->fileNamesList, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(showToImage(QListWidgetItem *)));
    connect(ui->fileNamesList, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)), this, SLOT(showToImage(QListWidgetItem *)));
}

SImageExInfos::~SImageExInfos()
{
    delete ui;
}

void SImageExInfos::showToText()
{
    if (m_curImage.isNull()) return ;

    QString str = "return \n{\n";
    for (int row = 0;row < m_curImage.height();++row)
    {
        str+= "\t{";
        for(int col = 0;col < m_curImage.width();++col)
        {
            QRgb rgba = m_curImage.pixel(col, row);
            int alpha = qAlpha(rgba);

            if (alpha == 0x00)
            {
                str += "0,";
            }else
            {
                str += "1,";
            }
        }
        str.chop(1);
        str+= "},\n";
    }
    str.chop(2);
    str += "\n}";
    ui->outTextEdit->setText(str);
}

void SImageExInfos::showToImage(QListWidgetItem *item)
{
    if (!item) return ;

    QUrl url;
    ui->fileNamesList->getUrl(&url,item);

    m_curImage.load(url.toLocalFile());
    QPixmap pixmap(QPixmap::fromImage(m_curImage));
    ui->outImage->setPixmap(pixmap);
}
