#include "su9Inject.h"
#include "ui_su9inject.h"
#include "Component/SU9InjectItem.h"
#include <QString>
#include <QDir>
#include <QDirIterator>

static const QString U9FOLDER_NAME = "u9";
static const QString COMMAND_PUSH_FILE_FORMAT = "mnt/sdcard/Android/data/%1/files/S/";  //目标目录

SU9Inject::SU9Inject(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SU9Inject)
{

    m_pAdbHelper = new SAdbHelper(this);
    m_pCommandRecord = new QStringList();

    ui->setupUi(this);

    ui->filesList->setDragTitleMode(SDragListWidget::DropItemTextMode::FileName);
    ui->filesList->setDragSortEnabled(true);
    ui->filesList->setRendererItem([this](QString itemName){
        SU9InjectItem *widget = new SU9InjectItem();
        widget->setState(&itemName,0);
        widget->setSelected(true);
        QListWidgetItem *item = new QListWidgetItem(ui->filesList);
        item->setSizeHint(QSize(widget->size()));
        ui->filesList->setItemWidget(item,widget);

        return item;
    });

    connect(ui->sendBtn,&QPushButton::clicked,this,&SU9Inject::sendSlot);
    connect(ui->refreshDeviceBtn,&QPushButton::clicked,this,&SU9Inject::refreshDevices);
    connect(ui->searchPackageBtn,&QPushButton::clicked,this,&SU9Inject::refreshPackages);
    connect(ui->injectBtn,&QPushButton::clicked,this,&SU9Inject::injectFiles);

    connect(m_pAdbHelper,SIGNAL(receive(QString)),this,SLOT(receiveSlot(QString)));
}


SU9Inject::~SU9Inject()
{
    delete ui;
    delete m_pAdbHelper;
    delete m_pCommandRecord;
}


void SU9Inject::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    refreshDevices();
}

QStringList SU9Inject::getFilesPaths()
{
    QStringList fileList;
    QList<QUrl> list;
    ui->filesList->getUrls(&list);

    if (list.length() <= 0)
        ui->filesList->getAllUrls(&list);

    for(int i = 0;i < list.length(); i++)
    {
        auto it = list[i];
        auto item = ui->filesList->itemWidget(ui->filesList->item(i));
        auto widget = static_cast<SU9InjectItem *>(item);
        if (!widget->isSelected())
            continue;

        QFileInfo fileInfo(it.toLocalFile());
        fileList.push_back(fileInfo.absoluteFilePath());
    }

    return fileList;
}

void SU9Inject::refreshDevices()
{
    auto devices = m_pAdbHelper->getDeviceNames();
    ui->devicesCob->clear();
    ui->devicesCob->addItems(devices);
    ui->devicesCob->repaint();
}

void SU9Inject::refreshPackages()
{
    auto packages = m_pAdbHelper->getPackageList();
    qSort(packages.begin(), packages.end(), [](const QString& s1, const QString& s2){
                return s1 < s2; });
    ui->packageCob->clear();
    ui->packageCob->addItems(packages);
    ui->packageCob->repaint();
}

void SU9Inject::refreshCommand()
{
    ui->commandCob->clear();
    ui->commandCob->addItems(*m_pCommandRecord);
}

void SU9Inject::injectFiles()
{
    auto fileList = getFilesPaths();
    auto packageName = ui->packageCob->currentText();

    QString tempFolder = copyAndCreateU9TempFolder(fileList,true);
    QString destFolder = QString(COMMAND_PUSH_FILE_FORMAT).arg(packageName);
    //TODO:需要将这批文件用luaPack打成U9在注入

    m_pAdbHelper->sendFilesCommand(tempFolder,destFolder);
    //可以移除临时目录
}

void SU9Inject::sendSlot()
{
    //获取command的内容,并发送
    auto commandStr = ui->commandCob->currentText();
    m_pAdbHelper->sendCustomCommand(commandStr);

    if (m_pCommandRecord->count() >= 5)
        m_pCommandRecord->pop_back();

    m_pCommandRecord->removeOne(commandStr);
    m_pCommandRecord->push_front(commandStr);

    refreshCommand();
}
void SU9Inject::receiveSlot(QString content)
{
    ui->consoleText->setText(content);
    ui->consoleText->moveCursor(QTextCursor::End);
    ui->consoleText->repaint();
}

//获取临时目前地址
QString SU9Inject::getTempU9Folder()
{
    QString aFile = QDir::currentPath();
    QString folder = QString("%1/%2").arg(aFile).arg(U9FOLDER_NAME);
    return folder;
}
//把预发送的文件拷贝到一个临时目录,发送完成情况
QString SU9Inject::copyAndCreateU9TempFolder(QStringList fileList, bool isClear)
{
    QString folderPath = getTempU9Folder();
    QDir dDir(folderPath);
    if (!dDir.exists(folderPath))
    {
        dDir.mkdir(folderPath);
    }

    if (isClear)
    {
        QDirIterator DirsIterator(folderPath, QDir::Files | QDir::AllDirs | QDir::NoDotAndDotDot, QDirIterator::NoIteratorFlags);
        while(DirsIterator.hasNext())
        {
            if (!dDir.remove(DirsIterator.next())) // 删除文件操作如果返回否，那它就是目录
            {
                QDir(DirsIterator.filePath()).removeRecursively(); // 删除目录本身以及它下属所有的文件及目录
            }
        }
    }

    qDebug()<<fileList;
    for(auto it : fileList)
    {
        QString srcFile = it;
        QFileInfo fileInfo(it);
        QString toFile = QString("%1/%2").arg(folderPath).arg(fileInfo.fileName());
        copyFileToPath(srcFile,toFile,true);
    }

    return folderPath;
}


//拷贝文件：
bool SU9Inject::copyFileToPath(QString sourceDir, QString toDir, bool coverFileIfExist)
{
    toDir.replace("\\","/");
    if (sourceDir == toDir){
        return true;
    }
    if (!QFile::exists(sourceDir)){
        return false;
    }
    QDir createfile;
    bool exist = createfile.exists(toDir);
    if (exist){
        if(coverFileIfExist){
            createfile.remove(toDir);
        }
    }

    if(!QFile::copy(sourceDir, toDir))
    {
        return false;
    }
    return true;
}

//拷贝文件夹：
bool SU9Inject::copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist)
{
    QDir sourceDir(fromDir);
    QDir targetDir(toDir);
    if(!targetDir.exists()){    /**< 如果目标目录不存在，则进行创建 */
        if(!targetDir.mkdir(targetDir.absolutePath()))
            return false;
    }

    QFileInfoList fileInfoList = sourceDir.entryInfoList();
    foreach(QFileInfo fileInfo, fileInfoList){
        if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")
            continue;

        if(fileInfo.isDir()){    /**< 当为目录时，递归的进行copy */
            if(!copyDirectoryFiles(fileInfo.filePath(),
                targetDir.filePath(fileInfo.fileName()),
                coverFileIfExist))
                return false;
        }
        else{            /**< 当允许覆盖操作时，将旧文件进行删除操作 */
            if(coverFileIfExist && targetDir.exists(fileInfo.fileName())){
                targetDir.remove(fileInfo.fileName());
            }

            /// 进行文件copy
            if(!QFile::copy(fileInfo.filePath(),
                targetDir.filePath(fileInfo.fileName()))){
                    return false;
            }
        }
    }
    return true;
}

