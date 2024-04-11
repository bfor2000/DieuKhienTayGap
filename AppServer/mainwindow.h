#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QtCore>
#include <QtWidgets>
#include <QtGui>
#include <QVideoWidget>
#include <QAudioOutput>
#include<QDebug>
#include <QDir>
#include<QTcpServer>
#include <QMessageBox>
#include <QHostAddress>
#include<QTcpSocket>
#include <QAbstractSocket>
#include <QIODevice>
#include <QVideoSink>
#include <QDataStream>
#include <QFile>
#include <QByteArray>
#include <QFileInfo>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct userSocket{
    QList<QString> user;
    QList<struct deviceSocket> listDevice;
};
struct deviceSocket{
    QString model;
    QString name;
    QJsonObject content;
    QTcpSocket *Socket;
};
struct registeReceiveData{
    QList<QTcpSocket*> listConnection;
    QList<QString> receiveJson;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void setData(QString command,QString messenger);
    void getData(QTcpSocket *Socket,QString messenger);

    void sendConnect(QTcpSocket *Socket);

    QJsonObject jsonDevice(QString messenger);

    void readFile(QString path);

    void sendFile(QString path,QTcpSocket *socket);

    QString getIpSocket(QTcpSocket *socket);

    void stateChangedSocket(QAbstractSocket::SocketState socketState);

    void addHistory(QString icon,QString ip="",QString messenger="");

    void readyReadData();

    void newConnect();

    void resizeEvent(QResizeEvent* event);

    QString Path(int value);

    QList<QString> List(QString path);

    void Play_video(QString path);

    QString convert_qint64_String(qint64 value);

    void positionChanged(qint64 position);

    void on_buttonOpen_clicked();

    void on_actionServer_triggered(bool checked);

    void on_actionVideo_triggered(bool checked);

    void on_actionLive_triggered(bool checked);

    void on_toolButton_clicked(bool checked);

    void on_horizontalSlider_2_valueChanged(int value);

    void on_buttonVolume_toggled(bool checked);

    void on_videoSpeed_valueChanged(int value);

    void on_timeSlider_actionTriggered(int action);

    void on_beforeVideo_clicked();

    void on_NextVideo_clicked();

    void on_videoTranslationLeft_clicked();

    void on_videoTranslationRight_clicked();

    void on_actionDataTransmission_triggered();

private:
    Ui::MainWindow *ui;
    QMediaPlayer *Play;
    QVideoWidget *video;
    QAudioOutput *audioOutput;
    QTcpServer *Server;
    registeReceiveData listReceive;
    QVideoSink *videoSink;
    userSocket listUser;

};

#endif // MAINWINDOW_H
