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

protected:
    bool pointCmp(const QPoint &a,const QPoint &b,const QPoint &center);
    QPoint shapeGravity(QVector<QPoint> &vPoints);  //返回多边形的重心
    void clockwiseSortPoints(QVector<QPoint> &vPoints);

    QString producePixmapInfo(const QImage *image);
    QString producePointInfo(const QImage *image,int density);
protected slots:
    void showToImage(QListWidgetItem *item);
    void showToText();
private:

    Ui::SImageExInfos *ui;
};

#endif // SIMAGEEXINFOS_H
