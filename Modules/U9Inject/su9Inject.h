#ifndef SU9INJECT_H
#define SU9INJECT_H

#include <QWidget>
#include <QString>
#include "Component/SAdbHelper.h"
namespace Ui {
class SU9Inject;
}

class SU9Inject : public QWidget
{
    Q_OBJECT

public:
    explicit SU9Inject(QWidget *parent = 0);
    ~SU9Inject();
public:
    QString getFilesPath();
protected slots:
    void sendSlot();
    void receiveSlot(QString);
private:
    Ui::SU9Inject *ui;
    SAdbHelper *m_pAdbHelper;

};

#endif // SU9INJECT_H
