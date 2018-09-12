#ifndef SCOORDINATEMEASURE_H
#define SCOORDINATEMEASURE_H

#include <QWidget>
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
private:
    Ui::SCoordinateMeasure *ui;
};

#endif // SCOORDINATEMEASURE_H
