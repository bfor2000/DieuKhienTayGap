#include "backend.h"
#include <QTcpSocket>
#include <QDebug>
#include <QJsonDocument>
#include <QIODevice>
#include <QQuickView>

Backend::Backend(QObject *parent)
    : QObject{parent}
{
    socket=new QTcpSocket;
    socket->connectToHost(QHostAddress::LocalHost,8081);
    connect(socket,&QIODevice::readyRead,this,&Backend::readData);
    socket->write("getAllDevice");

}

QStringList Backend::listSwitch(const QString &nameDevice)
{
    return mJsonDocument.object().value(nameDevice).toObject().value("content").toObject().keys();
}


QStringList Backend::listDevice(const QString &command)
{
    QStringList key=mJsonDocument.object().keys();
    if(command=="Device") return key;
    else{
        QStringList value;
        for(int i=0;i<key.count();i++)
            value<<mJsonDocument.object().value(key.value(i)).toObject().value(command).toString();
        return value;
    }
}

void Backend::setName(const QString command, const QString Device, const QString nameChanged, const QString key, const QString newName)
{
    QString commandClient;
    if(command=="name")
        commandClient=("setName:"+Device+"{"+nameChanged+"}");
    else
        commandClient=("setNameControl:"+Device+"{"+key+"}"+newName);
    socket->write(commandClient.toUtf8());
}

QString Backend::statusSwitch(const QString &command,const QString &nameDevice,const QString &nameSwitch)
{
    QJsonObject object(mJsonDocument.object().value(nameDevice).toObject().value("content").toObject());
    return object.value(nameSwitch).toObject().value(command).toString();
}

void Backend::setStatusSwitch(const QString &command,const QString &nameDevice, const QString &nameSwitch,const QString &newName,const bool status)
{
    QString commandClient;
    if(command=="data")
        commandClient="setData:"+nameDevice+"{"+nameSwitch+"}switch:"+(status?"on":"off");
    else
        commandClient="setNameControl:"+nameDevice+"{"+nameSwitch+"}"+newName;
    socket->write(commandClient.toUtf8());
}

void Backend::setJsonDevice(QJsonDocument json)
{
    if(json==mJsonDocument)
        return;
    mJsonDocument=json;
    emit jsonDocumentChanged();
}


void Backend::readData()
{
    QByteArray byteData=socket->readAll();
    setJsonDevice(QJsonDocument::fromJson(byteData));

}

