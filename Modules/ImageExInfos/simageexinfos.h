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
    QString producePixmapInfo(const QImage *image);
    QString producePointInfo(const QImage *image);
protected slots:
    void showToImage(QListWidgetItem *item);
    void showToText();
private:

    Ui::SImageExInfos *ui;
};

#endif // SIMAGEEXINFOS_H
