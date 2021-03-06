#ifndef SIMAGEEXINFOS_H
#define SIMAGEEXINFOS_H

#include <QWidget>
class QListWidgetItem;

namespace Ui {
class SImageExInfos;
}

class SImageExInfos : public QWidget
{
    Q_OBJECT
public:
    explicit SImageExInfos(QWidget *parent = 0);
    ~SImageExInfos();

public:

protected:
    bool pointCmp(const QPoint &a,const QPoint &b,const QPoint &center);
    QPoint shapeGravity(QVector<QPoint> &vPoints);  //返回多边形的重心
    void clockwiseSortPoints(QVector<QPoint> &vPoints);

    QString producePixmapInfo(const QImage *image);
    QString producePointInfo(const QImage *image,int density,QVector<QPoint> *points = nullptr);
    QString produceCustomInfo(const QImage *image,QVector<QPoint> *produceCustomInfo);
protected slots:
    void showToImage(QListWidgetItem *item);
    void showToText();
    void radioChanged(bool state);
private:
    int m_curTolerance;
    QPointF m_curAnchorPoint;
    Ui::SImageExInfos *ui;
};

#endif // SIMAGEEXINFOS_H
