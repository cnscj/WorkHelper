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

    ui->outTextEdit->setVisible(false);
}

SImageExInfos::~SImageExInfos()
{
    delete ui;
}

QString SImageExInfos::producePixmapInfo(const QImage *image)
{
    if ( !image || image->isNull()) return "";

    QString str = "return \n{\n";
    for (int row = 0;row < image->height();++row)
    {
        str+= "\t{";
        for(int col = 0;col < image->width();++col)
        {
            QRgb rgba = image->pixel(col, row);
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

    return str;
}
QString SImageExInfos::producePointInfo(const QImage *image)
{
    return "return {}";
    ////TODO:
    QList<QPoint> samplePointsList;
    int maxCol = image->width();
    int maxRow = image->height();

    int *curColLastRowState = new int[maxCol];
    memset(curColLastRowState,0,sizeof(int)*maxCol);

    for (int row = 0;row < maxRow;++row)
    {
        int curRowLastColState = 0;
        for(int col = 0;col < maxCol;++col)
        {
            //TODO:查找符合条件的像素
            QRgb rgba = image->pixel(col, row);
            int alpha = qAlpha(rgba);
            bool isMark = false;


            if ( isMark )
            {
                samplePointsList.push_back(QPoint(col,row));
            }
        }

    }
    delete curColLastRowState;

    //对点列表进行排序
    //TODO:从最左下顺时针-x最小,同x时y最小.
    QString str = "return \n{\n";
    for (const auto it:samplePointsList)
    {
        str += QString("{x = %1,y = %2},\n").arg(it.x()).arg(it.y());
    }
    str.chop(2);
    str += "\n}\n";

    return str;
}

void SImageExInfos::showToText()
{
    QString ret = "";
   if(ui->alphaRB->isChecked())
   {
       ret = producePixmapInfo(ui->imageView->image());
   }else
   {
       ret = producePointInfo(ui->imageView->image());
   }

    ui->outTextEdit->setVisible(true);
    ui->outTextEdit->setText(ret);
}

void SImageExInfos::showToImage(QListWidgetItem *item)
{
    if (!item) return ;

    QUrl url;
    ui->fileNamesList->getUrl(&url,item);
    ui->imageView->showImage(url.toLocalFile());

    ui->outTextEdit->setVisible(false);
    ui->outTextEdit->setText("");
}
