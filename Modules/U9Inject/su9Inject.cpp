#include "su9Inject.h"
#include "ui_su9inject.h"

SU9Inject::SU9Inject(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SU9Inject)
{

    m_pAdbHelper = new SAdbHelper(this);
    ui->setupUi(this);

    ui->filesList->setDragTitleMode(SDragListWidget::DropItemTextMode::FileName);
    ui->filesList->setDragSortEnabled(true);

    connect(ui->sendBtn,&QPushButton::clicked,this,&SU9Inject::sendSlot);
    connect(ui->refreshDeviceBtn,&QPushButton::clicked,this,&SU9Inject::refreshDevices);
    connect(ui->searchPackageBtn,&QPushButton::clicked,this,&SU9Inject::refreshPackages);
    connect(ui->injectBtn,&QPushButton::clicked,this,&SU9Inject::injectFiles);

    connect(m_pAdbHelper,SIGNAL(receive(QString)),this,SLOT(receiveSlot(QString)));
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

    for(auto it : list)
    {
        QFileInfo fileInfo(it.toLocalFile());
        fileList.push_back(fileInfo.absoluteFilePath());
    }

    return fileList;
}

void SU9Inject::refreshDevices()
{
    auto devices = m_pAdbHelper->getDeviceList();
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

void SU9Inject::injectFiles()
{
    auto fileList = getFilesPaths();
    auto packageName = ui->packageCob->currentText();
    m_pAdbHelper->sendFilesCommand(fileList,packageName);
}

void SU9Inject::sendSlot()
{
    //获取command的内容,并发送
    auto commandStr = ui->commandCob->currentText();
    m_pAdbHelper->sendCustomCommand(commandStr);
}
void SU9Inject::receiveSlot(QString content)
{
    ui->consoleText->setText(content);
    ui->consoleText->moveCursor(QTextCursor::End);
    ui->consoleText->repaint();
}

SU9Inject::~SU9Inject()
{
    delete ui;
    delete m_pAdbHelper;
}
