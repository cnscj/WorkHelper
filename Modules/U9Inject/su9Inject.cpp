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
    connect(m_pAdbHelper,SIGNAL(receive(QString)),this,SLOT(receiveSlot(QString)));
}

QString SU9Inject::getFilesPath()
{
    QString out = "";
    QList<QUrl> list;
    ui->filesList->getUrls(&list);

    if (list.length() <= 0)
        ui->filesList->getAllUrls(&list);

    for(auto it : list)
    {
        QFileInfo fileInfo(it.toLocalFile());
        out += QString("%1%2\r\n").arg(out).arg(fileInfo.absolutePath());
    }

    return out;
}

void SU9Inject::sendSlot()
{
    //获取command的内容,并发送
    auto commandStr = ui->commandCob->currentText();
    m_pAdbHelper->send(commandStr);
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
