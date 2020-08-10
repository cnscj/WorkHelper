#include "SAdbHelper.h"
#include <QDebug>
#include <QDateTime>
#include <QDir>
#include <QDirIterator>

static const QString MAC_ADB_PATH_FORMAT = "/Users/%1/Library/Android/sdk/platform-tools/%2";
static const QString COMMAND_GET_DEVICES = "adb devices";
static const QString COMMAND_GET_PACKAGES = "adb shell pm list packages";
static const QString COMMAND_PUSH_FILE_FORMAT = "adb push %1 mnt/sdcard/Android/data/%2/files/S/";  //目录 拷贝 到目录
static const QString U9FOLDER_NAME = "u9";

SAdbHelper::SAdbHelper(QObject *parent)
{
    m_pProcess = new QProcess();
    m_pProcess->open();

    connect(m_pProcess,&QProcess::readyReadStandardOutput,this,&SAdbHelper::receiveSlot);
}

SAdbHelper::~SAdbHelper()
{
    m_pProcess->close();
    delete m_pProcess;
}

void SAdbHelper::clear()
{
    m_content = "";
    emitContent();
}
QStringList SAdbHelper::getPackageList()
{
    QStringList packageList;
    send(false,COMMAND_GET_PACKAGES,[&](QString content){
        //解析设备列表
        auto contentList = content.split("\n");

        for(int i = 0;i < contentList.length();i++)
        {
            QString packageLine = contentList[i];
            QString headWord = "package:";
            if (packageLine.startsWith(headWord))
            {
                QString packageName = packageLine.mid(headWord.length());
                if (!packageName.isEmpty() && !packageName.isNull())
                {
                    packageList.push_back(packageName);
                }
            }


        }
    });
    return packageList;
}

QStringList SAdbHelper::getDeviceList()
{
    QStringList deviceList;
    send(false,COMMAND_GET_DEVICES,[&](QString content){
        //解析设备列表
        auto contentList = content.split("\n");

        for(int i = 1;i < contentList.length();i++) //第一行不算
        {
            QString deviceLine = contentList[i];    //设备
            if (!deviceLine.isEmpty() && !deviceLine.isNull())
            {
                deviceList.push_back(deviceLine);
            }

        }
    });
    return deviceList;
}

void SAdbHelper::sendCustomCommand(QString command)
{
    send(false,command,[&](QString content){
        appendContent(content,command);
        emitContent();
    });
}

void SAdbHelper::sendFilesCommand(QStringList fileList, QString packageName)
{
    //把文件拷贝到临时目录,发送
    QString tempFolder = copyAndCreateU9TempFolder(fileList,true);
    QString fullCommand = QString(COMMAND_PUSH_FILE_FORMAT).arg(tempFolder).arg(packageName);
    qDebug()<<fullCommand;
    send(false,fullCommand,[this](QString content){
        appendContent(content,COMMAND_PUSH_FILE_FORMAT);
        emitContent();
    });
}

void SAdbHelper::send(bool isAsync, QString command, FSendCallback func)
{
    QString uesrName = getUserName();
    QString fullCommand = QString(MAC_ADB_PATH_FORMAT).arg(uesrName).arg(command);
    m_pProcess->start(fullCommand);

    if (!isAsync)
    {
        m_pProcess->waitForFinished();//等待完成
    }

    if (func != nullptr)
    {
        QString content = m_pProcess->readAllStandardOutput();
        func(content);
    }

}

void SAdbHelper::appendContent(QString content,QString command)
{
    auto dateTime = QDateTime::currentDateTime();
    QString newContent = QString("[%1]:%2\n%3%4").arg(dateTime.toString("HH:MM:ss")).arg(command).arg(content).arg("");
    m_content.append(newContent);
}

void SAdbHelper::emitContent()
{
    emit receive(m_content);
}

QString SAdbHelper::getUserName()
{
    QString username = QDir::home().dirName();
    return username;
}

//获取临时目前地址
QString SAdbHelper::getTempU9Folder()
{
    QString aFile = QDir::currentPath();
    QString folder = QString("%1/%2").arg(aFile).arg(U9FOLDER_NAME);
    return folder;
}
//把预发送的文件拷贝到一个临时目录,发送完成情况
QString SAdbHelper::copyAndCreateU9TempFolder(QStringList fileList, bool isClear)
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

void SAdbHelper::receiveSlot()
{
    qDebug()<<"搜到有";
}

//拷贝文件：
bool SAdbHelper::copyFileToPath(QString sourceDir, QString toDir, bool coverFileIfExist)
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
bool SAdbHelper::copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist)
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
