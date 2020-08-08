#ifndef SADBHELPER_H
#define SADBHELPER_H
#include <QProcess>
#include <QObject>
class SAdbHelper : public QObject
{
    Q_OBJECT
public:
    SAdbHelper(QObject *parent = Q_NULLPTR);
    ~SAdbHelper();
public:
    QStringList getDeviceList();
public:
    void clear();
    void send(QString command);
    void close();
protected:
    void appendContent(QString content);
    void emitContent();
signals:
    void receive(QString content);
private:
    QProcess *m_pProcess;
    QString m_content;
};

#endif // SADBHELPER_H
