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
    bool isConnected();
    QStringList getPackageList();
    QStringList getDeviceList();
    QStringList getDeviceNames();
    void sendCustomCommand(QString content);
    void sendFilesCommand(QString srcFolder,QString destFolder);

    void clear();
    void send(bool isAsync, QString command, FSendCallback func);
protected:
    void appendContent(QString content,QString command);
    void emitContent();

    QString getUserName();
protected slots:
    void receiveSlot();
signals:
    void receive(QString content);
private:
    QProcess *m_pProcess;
    QString m_content;
};

#endif // SADBHELPER_H
