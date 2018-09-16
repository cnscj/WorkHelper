#include "simageexinfos.h"
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

    connect(ui->pointRB, SIGNAL(toggled(bool)), ui->sampleLineEdit, SLOT(setEnabled(bool)));

    ui->sampleLineEdit->setEnabled(false);
    ui->outTextEdit->setVisible(false);
    ui->sampleLineEdit->setValidator(new QIntValidator(0, 100, this));

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
        str+= "{";
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
QString SImageExInfos::producePointInfo(const QImage *image,int density)
{
    if ( !image || image->isNull()) return "";

    QVector<QPoint> samplePointsList;
    int maxCol = image->width();
    int maxRow = image->height();
    if (density < 0) density = 100;
    int colPointNum = maxCol * (1-density/100);
    int rowPointNum = maxRow * (1-density/100);
    colPointNum = colPointNum > 0 ? colPointNum : 1;
    rowPointNum = rowPointNum > 0 ? rowPointNum : 1;

    int *curColLastRowState = new int[maxCol];
    ::memset(curColLastRowState,0,sizeof(int)*maxCol);        //默认置0

    for (int row = 0;row < maxRow;++row)
    {
        int curRowLastColState = 0;                           //默认置0
        for(int col = 0;col < maxCol;++col)
        {
            QRgb rgba = image->pixel(col, row);
            int alpha = qAlpha(rgba);
            bool isMark = false;
            bool isColMask = false;
            bool isRowMask = false;

            if (alpha == 0x00)
            {
                if (curRowLastColState == 1)
                {
                    curRowLastColState = 0;
                }
                if (curColLastRowState[col] == 1)
                {
                    curColLastRowState[col] = 0;
                }
            }
            else
            {
                if (curRowLastColState == 0)
                {
                    isColMask = true;
                    curRowLastColState = 1;
                }
                else
                {
                    if (col >= maxCol-1)
                    {
                        isColMask = true;  //如果最后的像素不为0,记录
                    }
                    else
                    {
                        //读取下一个
                        QRgb rgba = image->pixel(col+1, row);
                        int alpha = qAlpha(rgba);
                        if (alpha == 0x00)
                        {
                            isColMask = true;  //下一个的像素如果是0,则记录当前
                        }
                    }
                }

                if (curColLastRowState[col] == 0)
                {
                    isRowMask = true;
                    curColLastRowState[col] = 1;
                }
                else
                {
                    if (row >= maxRow-1)
                    {
                        isRowMask = true;  //如果最后的像素不为0,记录
                    }
                    else
                    {
                        //读取下一个
                        QRgb rgba = image->pixel(col, row+1);
                        int alpha = qAlpha(rgba);
                        if (alpha == 0x00)
                        {
                            isRowMask = true;  //下一个的像素如果是0,则记录当前
                        }
                    }
                }
            }

            isMark = isColMask && isRowMask;

            if (col % colPointNum != 0 || row % rowPointNum != 0) isMark = false;

            if ( isMark )
            {
                samplePointsList.push_back(QPoint(col+1,row+1));
            }
        }

    }
    delete curColLastRowState;

    //对点列表进行排序
    clockwiseSortPoints(samplePointsList);
    QString str = "return \n{\n";
    for (const auto it:samplePointsList)
    {
        str += QString("{x = %1,y = %2},\n").arg(it.x()).arg(it.y());
    }
    str.chop(2);
    str += "\n}\n";

    return str;
}

//若点a大于点b,即点a在点b顺时针方向,返回true,否则返回false
bool SImageExInfos::pointCmp(const QPoint &a,const QPoint &b,const QPoint &center)
{
    if (a.x() >= 0 && b.x() < 0)
        return true;
//    if (a.x() == 0 && b.x() == 0)
//        return a.y() > b.y();
    //向量OA和向量OB的叉积
    int det = (a.x() - center.x()) * (b.y() - center.y()) - (b.x() - center.x()) * (a.y() - center.y());
    if (det < 0)
        return true;
    if (det > 0)
        return false;
    //向量OA和向量OB共线
    //OA与OB的方向问题,求两者夹角
    //同向时，以距离判断大小,如果都指向负轴,则d1 > d2,否则 d1 < d2
    //不同向指向指向负轴的优先为true
    int d1 = (a.x() - center.x()) * (a.x() - center.x()) + (a.y() - center.y()) * (a.y() - center.y());
    int d2 = (b.x() - center.x()) * (b.x() - center.x()) + (b.y() - center.y()) * (b.y() - center.y());

    if ((a.x() - center.x() < 0 && b.x() - center.x() < 0) ||
            (a.y() - center.y() > 0 && b.y() - center.y() > 0) ||
            (a.x() - center.x() < 0 && b.x() - center.x() > 0) ||
            (a.y() - center.y() > 0 && b.y() - center.y() < 0)

            )
        return d1 > d2;
    if ((a.x() - center.x() > 0 && b.x() - center.x() > 0) ||
            (a.y() - center.y() < 0 && b.y() - center.y() < 0) ||
            (a.x() - center.x() > 0 && b.x() - center.x() < 0) ||
            (a.y() - center.y() < 0 && b.y() - center.y() > 0)

            )
        return d1 < d2;

    return d1 > d2;
}

QPoint SImageExInfos::shapeGravity(QVector<QPoint> &vPoints)  //返回多边形的重心
{
    //法一:
//    double area = 0.f;
//    QPoint center;
//    float centerX = 0.f;
//    float centerY = 0.f;
//    int n = vPoints.size();
//    for (int i = 0; i < n - 1; i++)
//    {
//        area += (vPoints[i].x() * vPoints[i+1].y() - vPoints[i+1].x() * vPoints[i].y())/2.f;
//        centerX += (vPoints[i].x() * vPoints[i+1].y() - vPoints[i+1].x() * vPoints[i].y()) * (vPoints[i].x() + vPoints[i+1].x());
//        centerY += (vPoints[i].x() * vPoints[i+1].y() - vPoints[i+1].x() * vPoints[i].y()) * (vPoints[i].y() + vPoints[i+1].y());
//    }
//    area += (vPoints[n-1].x() * vPoints[0].y() - vPoints[0].x() * vPoints[n-1].y())/2.f;
//    centerX += (vPoints[n-1].x() * vPoints[0].y() - vPoints[0].x() * vPoints[n-1].y()) * (vPoints[n-1].x() + vPoints[0].x());
//    centerY += (vPoints[n-1].x() * vPoints[0].y() - vPoints[0].x() * vPoints[n-1].y()) * (vPoints[n-1].y() + vPoints[0].y());
//    centerX /= 6.f*area;
//    centerY /= 6.f*area;

//    center.setX((int)centerX);
//    center.setY((int)centerY);

    //法二:
    QPoint center;
    int x = 0,y = 0;
    int n = vPoints.size();
    for (int i = 0;i < n;i++)
    {
        x += vPoints[i].x();
        y += vPoints[i].y();
    }
    center.setX((int)(x/n));
    center.setY((int)(y/n));

    return center;
}
void SImageExInfos::clockwiseSortPoints(QVector<QPoint> &vPoints)
{
    //计算重心
    QPoint center = shapeGravity(vPoints);

    //冒泡排序-循环一次
    for(int i = 0;i < vPoints.size() - 1;i++)
    {
        for (int j = 0;j < vPoints.size();j++)
        {
            if (j< vPoints.size()-1)
            {
                if (pointCmp(vPoints[j],vPoints[j+1],center))
                {
                    QPoint tmp = vPoints[j];
                    vPoints[j] = vPoints[j + 1];
                    vPoints[j + 1] = tmp;
                }
            }
            else
            {
                if (pointCmp(vPoints[j],vPoints[0],center))
                {
                    QPoint tmp = vPoints[j];
                    vPoints[j] = vPoints[0];
                    vPoints[0] = tmp;
                }
            }
        }
    }
}


void SImageExInfos::showToText()
{
    QString ret = "";
   if(ui->alphaRB->isChecked())
   {
       ret = producePixmapInfo(ui->imageView->image());
       ui->imageView->setBackgroundColor(QColor(0,255,255));    //背景变色
   }
   else if (ui->pointRB->isChecked())
   {
       int density = 100;
       QString samlpeDensityStr = ui->sampleLineEdit->text();
       if (!samlpeDensityStr.isEmpty()) density = samlpeDensityStr.toInt();
       ret = producePointInfo(ui->imageView->image(),density);
   }
   else
   {
       //TODO:
       ret = "";
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
