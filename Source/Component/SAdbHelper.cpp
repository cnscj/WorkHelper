#include "SAdbHelper.h"
#include <QDebug>
#include <QDateTime>
#include <QDir>

static const QString MAC_ADB_PATH_FORMAT = "/Users/%1/Library/Android/sdk/platform-tools/%2";
static const QString COMMAND_GET_DEVICES_ID = "adb devices";
static const QString COMMAND_GET_DEVICES_NAME = "adb -d shell getprop ro.product.model";
static const QString COMMAND_GET_PACKAGES = "adb shell pm list packages";
static const QString COMMAND_PUSH_FILE_FORMAT = "adb push %1 %2";  //目录 拷贝 到目录


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

bool SAdbHelper::isConnected()
{
    auto devices = getDeviceList();
    return devices.length() > 0;
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
    send(false,COMMAND_GET_DEVICES_ID,[&](QString content){
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

QStringList SAdbHelper::getDeviceNames()
{
    QStringList deviceList;
    send(false,COMMAND_GET_DEVICES_NAME,[&](QString content){
        //解析设备列表
        auto contentList = content.split("\n");

        for(int i = 0;i < contentList.length(); i++)
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

void SAdbHelper::sendFilesCommand(QString srcFolder,QString destFolder)
{
    //发送
    QString fullCommand = QString(COMMAND_PUSH_FILE_FORMAT).arg(srcFolder).arg(destFolder);
    qDebug()<<fullCommand;
    send(false,fullCommand,[this](QString content){
        appendContent(content,"");
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

void SAdbHelper::appendContent(QString content, QString command)
{
    auto dateTime = QDateTime::currentDateTime();
    QString newContent = QString("[%1]:%2\n%3%4").arg(dateTime.toString("HH:MM:ss")).arg(command).arg(content).arg("");
    m_content.append(newContent);
}

void SAdbHelper::emitContent()
{
    emit receive(m_content);
}

void SAdbHelper::receiveSlot()
{
    qDebug()<<"搜到有";
}

QString SAdbHelper::getUserName()
{
    QString username = QDir::home().dirName();
    return username;
}

