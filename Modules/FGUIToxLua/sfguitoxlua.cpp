#include "sfguitoxlua.h"
#include "ui_sfguitoxlua.h"
#include <QFileDialog>
#include <QtXml>
#include <QDragEnterEvent>
#include <QRegExp>
#include "Component/sfguiobjectitem.h"
static const QString DEFAULT_TYPE = "Component";
QMap<QString,QString> initReplaceMap()
{
    QMap<QString,QString> map;
    //需要配对的类型
    map["list"] = "List";
    map["text"] = "Label";
    map["loader"] = "Loader";
    map["graph"] = "Graph";
    map["richtext"] = "RichText";
    map["image"] = "Image";
    map["button"] = "Button";
    map["progressbar"] = "ProgressBar";
//    map["group"] = DEFAULT_TYPE;

    return map;
}

QMap<QString,QString> initTmplMap()
{
    QMap<QString,QString> map;//需要配对的类型
    map["List"] =
"    {varName}:setState(function(data, index, comp, obj)\n"
"        obj.data = data\n"
"    end)\n"
"    {varName}:onClickItem(function(context)\n"
"        local data = context.data.data\n"
"    end)\n";

    map["Button"] =
"    {varName}:setClick(function(contxt)\n"
"        \n"
"    end)\n";

    return map;
}

static const QMap<QString,QString> REPLACE_MAP = initReplaceMap();
static const QMap<QString,QString> TMPL_MAP = initTmplMap();
static const QString PARENT_CTRL_NAME_PREFIX = "self.";
static const QString PARENT_CTRL_NAME = "self._root";
static const QString CHILD_CTRL_NAME_PREFIX = "local ";
static const QString CHILD_CTRL_NAME = "comp";

SFGUIToxLua::SFGUIToxLua(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SFGUIToxLua)
{
    ui->setupUi(this);
    this->setAcceptDrops(true);

    connect(ui->openBtn,&QPushButton::clicked,this,&SFGUIToxLua::openFile);
    connect(ui->refreshBtn,&QPushButton::clicked,this,&SFGUIToxLua::refreshSlot);
    connect(ui->produceBtn,&QPushButton::clicked,this,&SFGUIToxLua::produceSlot);

    connect(ui->childCodeChB,&QCheckBox::toggled,this,&SFGUIToxLua::childCodeChBSlot);
}

SFGUIToxLua::~SFGUIToxLua()
{
    delete ui;
}


void SFGUIToxLua::dragEnterEvent(QDragEnterEvent *event)
{
    //只接受Xml文件
   if (event->mimeData()->urls().count() > 0)
   {
       QString filePath = event->mimeData()->urls()[0].toLocalFile();
       if(!filePath.right(3).compare("xml",Qt::CaseInsensitive))
       {
           event->acceptProposedAction();//接受鼠标拖入事件
           return;
       }
   }
   event->ignore();//否则不接受鼠标事件
}
void SFGUIToxLua::dropEvent(QDropEvent *event)
{
    QString name = event->mimeData()->urls()[0].toLocalFile();
    ui->pathLe->setText(name);

    praseXml();
}

void SFGUIToxLua::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"),"/",tr("xml Files (*.xml)"));
    ui->pathLe->setText(fileName);

    praseXml();
}

void SFGUIToxLua::praseXml()
{
    //清空数据
    m_data.clear();
    ui->codeEdit->clear();

    //打开或创建文件
    QString path = ui->pathLe->text();
    QFile file(path);
    if(!file.open(QFile::ReadOnly))
        return;

    QDomDocument doc;
    if(!doc.setContent(&file))
    {
        file.close();
        return;
    }
    file.close();

    QDomElement root=doc.documentElement(); //返回根节点
    QDomNode node=root.firstChild(); //获得第一个子节点
    while(!node.isNull())  //如果节点不空
    {
        if(node.isElement()) //如果节点是元素
        {
            QDomElement e = node.toElement(); //转换为元素，注意元素和节点是两个数据结构，其实差不多
            if (e.nodeName() == "displayList")
            {
                QDomNodeList list=e.childNodes();
                for(int i=0;i<list.count();i++) //遍历子元素，count和size都可以用,可用于标签数计数
                {
                    QDomNode n=list.at(i);
                    if(node.isElement())
                    {
                        SFGUIObjectItemData data;

                        QString objType = n.nodeName();
                        QDomElement ee = n.toElement();
                        QString objName = ee.attribute("name");
                        QString realType = "";
                        QRegExp rx("(^n\\d*$)");
                        //////
                        if (objType == "component")
                        {
                            QString fileName = ee.attribute("fileName");
                            QFileInfo fileInfo(fileName);
                            realType = fileInfo.baseName();
                            if(ee.isElement()) //如果节点是元素
                            {
                                QDomNode eeNode=ee.lastChild(); //取最后一个
                                if (!eeNode.isNull())
                                {
                                    QString eeType = eeNode.nodeName();
                                    if (eeType != "relation")
                                    {
                                        realType = eeType;
                                    }
                                }
                            }
                        }
                        else if(objType == "text")
                        {
                            QString inputStr = ee.attribute("input");
                            if (inputStr != "")
                            {
                                QVariant tempValue = inputStr;
                                bool isInput = tempValue.toBool();
                                if (isInput)
                                {
                                    realType = "TextInput";
                                }
                            }
                        }

                        ///////
                        if (realType == "")
                        {
                            if (REPLACE_MAP.find(objType) != REPLACE_MAP.end())
                            {
                                realType = REPLACE_MAP[objType];
                            }
                            else
                            {
                                realType = DEFAULT_TYPE;
                            }
                        }
                        data.index = i+1;
                        data.isDefaultName = (rx.indexIn(objName) != -1) ;
                        data.name = objName;
                        data.oriType = objType;
                        data.type = realType;

                        m_data.push_back(data);

                    }
                }
            }
        }
        node = node.nextSibling(); //下一个兄弟节点,nextSiblingElement()是下一个兄弟元素，都差不多
    }

    setListProvider(m_data);
    produceSlot();
}


void SFGUIToxLua::setListProvider(const QLinkedList<SFGUIObjectItemData> &list)
{
    clearAllObjects();

    int i = 0;
    foreach (auto it, list)
    {

        SFGUIObjectItem *widget = new SFGUIObjectItem();
        widget->setState(it,i);
        //
        if (ui->outDefNameCb->isChecked())
        {
            widget->setEnabled(true);
        }else
        {
            widget->setEnabled(!it.isDefaultName);
        }
        //
        QListWidgetItem *item = new QListWidgetItem(ui->objList);
        ui->objList->addItem(item);
        item->setSizeHint(QSize(widget->size()));
        ui->objList->setItemWidget(item,widget);

        i++;
    }
}
void SFGUIToxLua::clearAllObjects()
{
    int count = ui->objList->count();
    for(int index = 0; index < count; index++)
    {
        QListWidgetItem *item = ui->objList->takeItem(0);
        delete item;
    }
}

void SFGUIToxLua::refreshSlot()
{
    praseXml();
//    setListProvider(m_data);
}
void SFGUIToxLua::produceSlot()
{
    SFGUIObjectItem::OutputParams params;
    params.prefix = ui->prefixLe->text();
    params.parentName = ui->parentNameLe->text();
    params.isFirstUpper = ui->firstCharUpper->isChecked();

    QString initHead ="function M:_initUI()\n";

    int count = ui->objList->count();
    QString varPreStr = "";
    if (true)
    {
        for(int index = 0; index < count; index++)
        {
            auto item = static_cast<SFGUIObjectItem *>(ui->objList->itemWidget(ui->objList->item(index)));
            if (item->isEnabled())
            {
                varPreStr = varPreStr + "    " + item->getPlaceholderString(params) + "\n";
            }
        }
    }

    QString varStr = "";
    for(int index = 0; index < count; index++)
    {
        auto item = static_cast<SFGUIObjectItem *>(ui->objList->itemWidget(ui->objList->item(index)));
        if (item->isEnabled())
        {
            if (ui->useIndexCb->isChecked())
            {
                varStr = varStr + "    " +item->getOutStringByIndex(params) + "\n";
            }
            else
            {
                varStr = varStr + "    " +item->getOutStringByName(params) + "\n";
            }
        }
    }

    QString varPostStr = "";
    if (ui->genPostCodeChb->isChecked())
    {
        for(int index = 0; index < count; index++)
        {
            auto item = static_cast<SFGUIObjectItem *>(ui->objList->itemWidget(ui->objList->item(index)));
            if (item->isEnabled())
            {
                auto data = item->getData();
                if (TMPL_MAP.find(data.type) != TMPL_MAP.end())
                {
                    QString codeTmpl = TMPL_MAP[data.type];
                    QString codeContent = codeTmpl.replace("{varName}",item->getOutVarName(params));
                    varPostStr = varPostStr + codeContent + "\n";
                }
            }
        }
    }

    QString initTrail = "end";

    ui->codeEdit->setText(initHead+varPreStr+"\n"+varStr+"\n"+varPostStr+initTrail);
    ui->codeEdit->update();
}

void SFGUIToxLua::childCodeChBSlot(bool isChecked)
{
    if (isChecked)
    {
        ui->prefixLe->setText(CHILD_CTRL_NAME_PREFIX);
        ui->parentNameLe->setText(CHILD_CTRL_NAME);
    }
    else
    {
        ui->prefixLe->setText(PARENT_CTRL_NAME_PREFIX);
        ui->parentNameLe->setText(PARENT_CTRL_NAME);
    }
}
