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

private:
    QString getTempU9Folder();
    QString copyAndCreateU9TempFolder(QStringList fileList,bool isClear);

    bool copyFileToPath(QString sourceDir, QString toDir, bool coverFileIfExist);
    bool copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist);
protected slots:
    void injectFiles();
    void sendSlot();
    void receiveSlot(QString);

    void packageChanged(QString);

    virtual void showEvent(QShowEvent *event);
private:
    Ui::SU9Inject *ui;
    SAdbHelper *m_pAdbHelper;
    QStringList *m_pCommandRecord;

    QString lastSelectPackageName;
};

#endif // SU9INJECT_H
