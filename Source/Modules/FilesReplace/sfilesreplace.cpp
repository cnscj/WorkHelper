#include "sfilesreplace.h"
#include "ui_sfilesreplace.h"

SFilesReplace::SFilesReplace(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SFilesReplace)
{
    ui->setupUi(this);

    ui->srcFileList->setDragTitleMode(SDragListWidget::DropItemTextMode::FilePath);
    ui->destFileList->setDragTitleMode(SDragListWidget::DropItemTextMode::FilePath);

    connect(ui->replaceBtn, SIGNAL(clicked()), this, SLOT(copyFiles()));
    connect(ui->srcFileList, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)), this, SLOT(showToSrcImage(QListWidgetItem *)));
    connect(ui->destFileList, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)), this, SLOT(showToDestImage(QListWidgetItem *)));
    connect(ui->srcFileList, SIGNAL(currentRowChanged(int)), this, SLOT(srcListRowChanged(int)));

    ui->destFileList->setDragSortEnabled(true);
    ui->srcFileList->setDragSortEnabled(true);
    connect(ui->srcFileList, SIGNAL(currentRowChanged(int)), ui->destFileList, SLOT(setSwapRow(int)));
    connect(ui->destFileList, SIGNAL(keySortFinished()), ui->srcFileList, SLOT(nextItem()));
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
/////////////
void SFilesReplace::copyFiles()
{

    QList<QUrl> srcUrlList;
    ui->srcFileList->getAllUrls(&srcUrlList);

    QList<QUrl> destUrlList;
    ui->destFileList->getAllUrls(&destUrlList);

    //复制文件的操作
//    int minLength = srcUrlList.length()>destUrlList.length()?srcUrlList.length():destUrlList.length();
    QString destRoot;
    ui->destFileList->removeAllUrlItems();
    for(int i = 0; i<srcUrlList.length(); i++)
    {
        QString newFilePath;
        if ( i<destUrlList.length() )
        {
            auto srcFilePath = srcUrlList.at(i).toLocalFile();
            auto destFilePath = destUrlList.at(i).toLocalFile();
//            QFileInfo srcFileInfo(srcFilePath);
            QFileInfo destFileInfo(destFilePath);
            destRoot = destFileInfo.path();

            //开始替换
            bool useDestName = ui->destNameRB->isChecked() ? true : false;
            copyFileToFile(srcFilePath,destFilePath,&newFilePath,useDestName);
        }
        else
        {
            //开始复制
            auto srcFilePath = srcUrlList.at(i).toLocalFile();
            copyFileToPath(srcFilePath,destRoot,&newFilePath,true);
        }
        ui->destFileList->addUrlItem(QUrl("file://"+newFilePath));
    }

}

bool SFilesReplace::copyFileToPath(QString sourceDir ,QString toDir,QString *newFilePath, bool coverFileIfExist)
{
    toDir.replace("\\","/");
    if (sourceDir == toDir)
    {
        return true;
    }
    if (!QFile::exists(sourceDir))
    {
        return false;
    }
    QDir createfile;
    bool exist = createfile.exists(toDir);
    if (exist)
    {
        if(coverFileIfExist)
        {
            createfile.remove(toDir);
        }
    }

    QFileInfo srcFileInfo(sourceDir);
    QString finalFile = toDir + "/" + srcFileInfo.fileName();
    if ( newFilePath ) *newFilePath = finalFile;
    if(!QFile::copy(sourceDir, finalFile))
    {
        return false;
    }
    return true;
}

bool SFilesReplace::copyFileToFile(QString srcFile ,QString destFile,QString *newFilePath, bool useDestName)
{
    if ( !QFile::exists(srcFile) )
        return false;

    QFileInfo srcFileInfo(srcFile);
    QFileInfo destFileInfo(destFile);

    QString destFileRoot = destFileInfo.path();
    QString newFileName = useDestName?destFileInfo.fileName():srcFileInfo.fileName();

    //移除目标文件
    QFile file(destFile);
    if (file.exists()) file.remove();

    QString finalFile = destFileRoot + "/" + newFileName;
    if ( newFilePath ) *newFilePath = finalFile;

    if(!QFile::copy(srcFile, finalFile))
    {
        return false;
    }
    return true;
}
