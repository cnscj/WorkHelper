#ifndef SCOORDINATEMEASURE_H
#define SCOORDINATEMEASURE_H

#include <QWidget>
#include "simginfo.h"
class QListWidgetItem;

namespace Ui {
class SCoordinateMeasure;
}

class SCoordinateMeasure : public QWidget
{
    Q_OBJECT
public:
    explicit SCoordinateMeasure(QWidget *parent = 0);
    ~SCoordinateMeasure();
protected slots:
     void showToImage(QListWidgetItem *item);
     void showImgInfo(SImgInfo &);

     void adjustView(QPoint pos);      //缩放调整视窗
private:
    Ui::SCoordinateMeasure *ui;
};

#endif // SCOORDINATEMEASURE_H
