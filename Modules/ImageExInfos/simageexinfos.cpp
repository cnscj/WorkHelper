#include "Modules/ImageExInfos/simageexinfos.h"
#include "ui_simageexinfos.h"

SImageExInfos::SImageExInfos(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SImageExInfos),
    m_pCurImage(nullptr)
{
    ui->setupUi(this);
    ui->fileNamesList->setDragTitleMode(SDragListWidget::DargTitleMode::FileName);

    connect(ui->produceBtn, SIGNAL(clicked()), this, SLOT(showToText()));
    connect(ui->fileNamesList, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(showToImage(QListWidgetItem *)));
}

SImageExInfos::~SImageExInfos()
{
    delete ui;
    if (m_pCurImage) delete m_pCurImage;
}

void SImageExInfos::showToText()
{
    if (!m_pCurImage) return;

    QString str = "return \n{";
    for (int  row= 0;row < m_pCurImage->height();++row)
    {
        str+= "\n";
        for(int col = 0;col < m_pCurImage->width();++col)
        {
            QRgb rgba = m_pCurImage->pixel(col, row);
            int alpha = qAlpha(rgba);

            if (alpha == 0x00)
            {
                str += "0,";
            }else
            {
                str += "1,";
            }
        }
    }
    str += "\n}";
    ui->outTextEdit->setText(str);
}

void SImageExInfos::showToImage(QListWidgetItem *item)
{
    if (!item) return ;

    if (m_pCurImage)
    {
        delete m_pCurImage;
        m_pCurImage = nullptr;
    }

    m_pCurImage = new QImage();
    QUrl url;
    ui->fileNamesList->getUrl(&url,item);

    m_pCurImage->load(url.toLocalFile());
    QPixmap pixmap(QPixmap::fromImage(*m_pCurImage));
    ui->outImage->setPixmap(pixmap);
}
