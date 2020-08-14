#ifndef SU9INJECT_H
#define SU9INJECT_H

#include <QWidget>
#include <QString>
#include <QSet>
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
    QStringList getFilesPaths();
protected:
    void refreshDevices();
    void refreshPackages();

    void refreshCommand();
protected slots:
    void injectFiles();
    void sendSlot();
    void receiveSlot(QString);

    virtual void showEvent(QShowEvent *event);
private:
    Ui::SU9Inject *ui;
    SAdbHelper *m_pAdbHelper;
    QStringList *m_pCommandRecord;

};

#endif // SU9INJECT_H
