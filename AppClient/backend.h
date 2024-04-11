#ifndef BACKEND_H
#define BACKEND_H
#include <QObject>
#include <QtQml>

class Backend : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit Backend(QObject *parent = nullptr);
    Q_INVOKABLE QStringList listDevice(const QString &command);
    Q_INVOKABLE void setName(const QString command,const QString Device, const QString nameChanged="",const QString key="",const QString newName="");
    Q_INVOKABLE QStringList listSwitch(const QString &nameDevice);
    Q_INVOKABLE QString statusSwitch(const QString &command,const QString &nameDevice,const QString &nameSwitch);
    Q_INVOKABLE void setStatusSwitch(const QString &command,const QString &nameDevice, const QString &nameSwitch, const QString &newName="",const bool status=false);
signals:
    void jsonDocumentChanged();
private:
    void setJsonDevice(QJsonDocument json);
    QTcpSocket *socket;
    void readData();
    QJsonDocument mJsonDocument;
};

#endif // BACKEND_H
