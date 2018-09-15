#ifndef SFILESREPLACE_H
#define SFILESREPLACE_H

#include <QWidget>
class QListWidgetItem;
namespace Ui {
class SFilesReplace;
}

class SFilesReplace : public QWidget
{
    Q_OBJECT

public:
    explicit SFilesReplace(QWidget *parent = 0);
    ~SFilesReplace();

protected:

    bool copyFileToPath(QString sourceDir ,QString toDir, QString *newFilePath,bool coverFileIfExist);
    bool copyFileToFile(QString sourceFile ,QString destFile, QString *newFilePath, bool useDestName);
protected slots:
    void copyFiles();
    void showToSrcImage(QListWidgetItem *item);
    void showToDestImage(QListWidgetItem *item);
protected slots:
    void srcListRowChanged(int row);
private:
    Ui::SFilesReplace *ui;
};

#endif // SFILESREPLACE_H
