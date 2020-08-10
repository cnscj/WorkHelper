#ifndef SADBHELPER_H
#define SADBHELPER_H
#include <QProcess>
#include <QObject>
class SAdbHelper : public QObject
{
    Q_OBJECT
public:
    typedef std::function<void (QString)> FSendCallback;
    SAdbHelper(QObject *parent = Q_NULLPTR);
    ~SAdbHelper();
public:
    QStringList getPackageList();
    QStringList getDeviceList();
    void sendCustomCommand(QString content);
    void sendFilesCommand(QStringList fileList,QString packageName);

    void clear();
    void send(bool isAsync, QString command, FSendCallback func);
protected:
    void appendContent(QString content,QString command);
    void emitContent();

    QString getUserName();
    QString getTempU9Folder();
    QString copyAndCreateU9TempFolder(QStringList fileList,bool isClear);

    bool copyFileToPath(QString sourceDir, QString toDir, bool coverFileIfExist);
    bool copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist);
protected slots:
    void receiveSlot();
signals:
    void receive(QString content);
private:
    QProcess *m_pProcess;
    QString m_content;
};

#endif // SADBHELPER_H
