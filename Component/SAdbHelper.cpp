#include "SAdbHelper.h"
#include <QDebug>
#include <QDateTime>
static const QString DEVICES_COMMAND_WORD = "adb devices";

SAdbHelper::SAdbHelper(QObject *parent)
{
    m_pProcess = new QProcess(parent);

}

void SAdbHelper::clear()
{
    m_content = "";
    emitContent();
}
QStringList SAdbHelper::getDeviceList()
{
    QStringList deviceList;

    m_pProcess->execute(DEVICES_COMMAND_WORD);
    m_pProcess->waitForFinished();//等待完成
    QString content = m_pProcess->readAllStandardOutput();
    //TODO:解析设备列表

}

void SAdbHelper::send(QString command)
{
    m_pProcess->open();
    m_pProcess->start();
    m_pProcess->execute(command);
    m_pProcess->waitForFinished();//等待完成
    QString content = m_pProcess->readAllStandardError();

    appendContent(content);
    emitContent();

    /// Users/cnscj/Library/Android/sdk/platform-tools/adb devices
    qDebug()<<QString::fromLocal8Bit(m_pProcess->readAll());
    qDebug()<<QString::fromLocal8Bit(m_pProcess->readAllStandardError());
    qDebug()<<QString::fromLocal8Bit(m_pProcess->readAllStandardOutput());
}

void SAdbHelper::close()
{
    m_pProcess->close();
}
void SAdbHelper::appendContent(QString content)
{
    auto dateTime = QDateTime::currentDateTime();
    QString newContent = QString("[%1]:%2%3").arg(dateTime.toString("HH:MM:ss")).arg(content).arg("\r\n");
    m_content.append(newContent);
}
void SAdbHelper::emitContent()
{
    emit receive(m_content);
}

SAdbHelper::~SAdbHelper()
{
    m_pProcess->close();
    delete m_pProcess;
}
