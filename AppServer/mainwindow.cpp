#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    Play=new QMediaPlayer;
    video= new QVideoWidget;
    audioOutput = new QAudioOutput;
    connect(Play,&QMediaPlayer::positionChanged,this,&MainWindow::positionChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setData(QString command,QString messenger)
{
    QString user=messenger.sliced(messenger.indexOf(":")+1,messenger.indexOf("{")-messenger.indexOf(":")-1);
    QString key=messenger.sliced(messenger.indexOf("{")+1,messenger.indexOf("}")-messenger.indexOf("{")-1);
    QString variable=messenger.sliced(messenger.indexOf("}")+1,messenger.length()-messenger.indexOf("}")-1);
    int index=listUser.user.indexOf(user);
    QJsonObject content;
    if(command=="status"){
        QJsonObject object(listUser.listDevice.value(index).content.value(key).toObject());
        object[variable.sliced(0,variable.indexOf(":"))]=variable.sliced(variable.indexOf(":")+1,variable.length()-variable.indexOf(":")-1);
        content=object;
    }
    else
        content["name"]=variable;
    (listUser.listDevice.data()+index)->content.find(key).operator *()=content;

    for(int i=0;i<listReceive.listConnection.count();i++)
        if(listReceive.receiveJson.value(i)=="1")
            sendConnect(listReceive.listConnection.value(i));

        else{
            int index=listUser.user.indexOf(user);
            QString temp=key+":"+
                           listUser.listDevice.value(index).content.value(key).toObject().value(variable.sliced(0,variable.indexOf(":"))).toString();
            listReceive.listConnection.value(i)->write(temp.toUtf8());
        }

}

void MainWindow::getData(QTcpSocket *Socket, QString messenger)
{
    QString user=messenger.sliced(messenger.indexOf(":")+1,messenger.indexOf("{")-messenger.indexOf(":")-1);
    QString key=messenger.sliced(messenger.indexOf("{")+1,messenger.indexOf("}")-messenger.indexOf("{")-1);
    QString variable=messenger.sliced(messenger.indexOf("}")+1,messenger.length()-messenger.indexOf("}")-1);
    int index=listUser.user.indexOf(user);
    Socket->write(listUser.listDevice.value(index).content.value(key).toObject().value(variable).toString().toUtf8());
}

void MainWindow::sendConnect(QTcpSocket *Socket)
{
    QJsonObject jsonUser;
    for(int i=0;i<listUser.user.length();i++){
        QJsonObject jsonContent;
        jsonContent["name"]=listUser.listDevice.value(i).name;
        jsonContent["content"]=listUser.listDevice.value(i).content;
        jsonContent["model"]=listUser.listDevice.value(i).model;
        jsonUser[listUser.user.value(i)]=jsonContent;
    }
    QJsonDocument dataWrite(jsonUser);
    Socket->write(dataWrite.toJson());
}

QJsonObject MainWindow::jsonDevice(QString messenger)
{
    QJsonObject object;
    int index=0;
    while(messenger.indexOf("{",index+1)!=-1){
        index=messenger.indexOf("{",index+1);
        QString data=messenger.sliced(index+1,messenger.indexOf("}",index+1)-index-1);
        int i=0;
        QJsonObject jsonObj;
        while(data.indexOf("(",i+1)!=-1){
            i=data.indexOf("(",i+1);
            QString listObject=data.sliced(i+1,data.indexOf(")",i+1)-i-1);
            jsonObj[listObject.sliced(0,listObject.indexOf(":"))]=listObject.sliced(listObject.indexOf(":")+1,listObject.length()-listObject.indexOf(":")-1);
        }
        object[data.sliced(0,data.indexOf("("))]=jsonObj;
    }
    return object;
}

void MainWindow::readFile(QString path)
{

}

void MainWindow::sendFile(QString path,QTcpSocket *socket)
{
    QFile file(path);
    if (file.open(QIODevice::ReadOnly)){
        QFileInfo info(file);
        QByteArray header("{name:"+info.fileName().toUtf8()+"}");
        QDataStream socketstream(socket);
        socketstream.setVersion(QDataStream::Qt_6_5);
        QByteArray contentFile=file.readAll();
        contentFile.prepend(header);
        socketstream<<contentFile;
    }else
        QMessageBox::information(this,"Errror","File not open");
}

QString MainWindow::getIpSocket(QTcpSocket *socket)
{
    return socket->peerAddress().toString()+":"+QString::number(socket->peerPort());
}

void MainWindow::stateChangedSocket(QAbstractSocket::SocketState socketState)
{
    QTcpSocket *socket=reinterpret_cast<QTcpSocket*>(sender());
    if(socketState==6){
        addHistory("unlink",getIpSocket(socket));
        int remove=listReceive.listConnection.indexOf(socket);
        listReceive.listConnection.remove(remove);
        listReceive.receiveJson.remove(remove);
    }
}

void MainWindow::addHistory(QString icon, QString ip, QString messenger)
{
    QListWidgetItem *item=new QListWidgetItem;
    QTime *time=new QTime;
    item->setIcon(QIcon("D:/Code/QtCreator/Server/image/"+icon+".png"));
    QString events;
    if(icon.startsWith("link"))
        events=" Connect to Server";
    else if(icon.startsWith("unlink"))
        events=" Disconnect to Server";
    else if(icon.startsWith("start"))
        events=" Server start";
    else if(icon.startsWith("stop"))
        events=" Server stop";
    else if(icon.startsWith("receive"))
        events=" Socket send messenger: ";
    item->setText(time->currentTime().toString()+" "+ip+events+messenger);
    ui->listTransmission->insertItem(0,item);
}



void MainWindow::readyReadData()
{
    QTcpSocket *socket=reinterpret_cast<QTcpSocket*>(sender());
    QString messenger=socket->readLine();
    addHistory("receive",socket->peerAddress().toString()+":"+QString::number(socket->peerPort()),messenger);
    if(messenger.startsWith("Get file:"))
        sendFile("data/version.txt",socket);
    else if(messenger.startsWith("Creater device:")){
        //Creater device:azyt5{quat tran(switch:on)(name:quat tran)}{quat cay(switch:off)(name:quat tran)}congtac
        QString device=messenger.sliced(messenger.indexOf(":")+1,messenger.indexOf("{")-messenger.indexOf(":")-1);
        QString model=messenger.sliced(messenger.lastIndexOf("}")+1,messenger.length()-messenger.lastIndexOf("}")-1);
        if(listUser.user.indexOf(device)==-1){
            listUser.user.append(device);
            struct deviceSocket newDevice;
            newDevice.model=model;
            newDevice.name=device;
            newDevice.content=jsonDevice(messenger);
            newDevice.Socket=socket;
            listUser.listDevice.append(newDevice);
            socket->write("Create complete!");
        }else
            socket->write("Device exist!");
        for(int i=0;i<listReceive.listConnection.count();i++)
            if(listReceive.receiveJson.value(i)=="1")
                sendConnect(listReceive.listConnection.value(i));

    }else if(messenger.startsWith("All:")){
        //All:messenger
        QString messengerAll=messenger.sliced(messenger.indexOf(":")+1);
        foreach (auto deviceOnline, listReceive.listConnection) {
            if(deviceOnline!=socket)
                deviceOnline->write(messengerAll.toUtf8());
        }
        socket->write("Send all complete!");
    }else if(messenger.startsWith("getAllDevice")){
        //getAllDevice
        sendConnect(socket);
    }else if(messenger.startsWith("getData:")){
        //getData:azyt5{quat tran}set
        getData(socket,messenger);
    }else if(messenger.startsWith("setData:")){
        //setData:azyt5{pin5}set:on
        setData("status",messenger);
    }else if(messenger.startsWith("setName:")){
        //setName:ate555{new name}
        QString user=messenger.sliced(messenger.indexOf(":")+1,messenger.indexOf("{")-messenger.indexOf(":")-1);
        QString name=messenger.sliced(messenger.indexOf("{")+1,messenger.indexOf("}")-messenger.indexOf("{")-1);
        int index=listUser.user.indexOf(user);
        (listUser.listDevice.data()+index)->name=name;
        for(int i=0;i<listReceive.listConnection.count();i++)
            if(listReceive.receiveJson.value(i)=="1")
                sendConnect(listReceive.listConnection.value(i));
    }else if(messenger.startsWith("register:")){
        QString resceive=messenger.at(messenger.length()-1);
        int index=listReceive.listConnection.indexOf(socket);
        *(listReceive.receiveJson.data()+index)=resceive;
    }else if(messenger.startsWith(("setNameControl:"))){
        //setNameControl:ate555{dieu hoa}khong phai dieu hoa
        setData("name",messenger);
    }else if(messenger.startsWith("Connection:")){
        //Connection:ate55
        QString device=messenger.sliced(messenger.indexOf(":")+1,messenger.length()-messenger.indexOf(":")-1);
        qDebug()<<device;
        int index=listUser.user.indexOf(device);
        if(index!=-1)
            (listUser.listDevice.data()+index)->Socket=socket;
    }else if(messenger.startsWith("Device:")){
        QString device=messenger.sliced(messenger.indexOf(":")+1,messenger.length()-messenger.indexOf(":")-1);
        qDebug()<<listUser.user<<device;
        if(listUser.user.indexOf(device)!=-1)
            socket->write("exist");
        else
            socket->write("not exist");
    }

}
void MainWindow::newConnect()
{
    if(Server->hasPendingConnections()){
        QTcpSocket *socket=new QTcpSocket;
        socket=Server->nextPendingConnection();
        listReceive.listConnection.append(socket);
        listReceive.receiveJson.append("1");
        connect(socket,&QIODevice::readyRead,this,&MainWindow::readyReadData);
        connect(socket,&QAbstractSocket::stateChanged,this,&MainWindow::stateChangedSocket);
        addHistory("link",getIpSocket(socket));

    }
}


void MainWindow::resizeEvent(QResizeEvent *Event)
{
    video->setGeometry(0,0,ui->Video->width(),ui->Video->height());
}

QString MainWindow::Path(int value)
{
    QList<QString> listFile=List("Video/");
    int index;
    for(int i=0;i<listFile.count();i++)
        if(listFile.value(i)==(Play->source()).fileName())
            index=i;
    index=listFile.count()-1?0:index+value;
    return "Video/"+listFile.value(index);
}

QList<QString> MainWindow::List(QString path)
{
    QList<QString> content;
    QDir dir("Video/");
    for (const QString &filename : dir.entryList(QDir::Files))
        content.append(filename);
    return content;
}

void MainWindow::Play_video(QString path)
{
    Play->setAudioOutput(audioOutput);
    video->setGeometry(0,0,ui->Video->width(),ui->Video->height());
    video->setParent(ui->scrollAreaWidgetContents_2);
    Play->setVideoOutput(video);
    Play->setSource(QUrl(path));
    ui->timeMaxVideo->setText(convert_qint64_String((int)(Play->duration())/1000));
    ui->timeSlider->setMaximum((int)(Play->duration())/1000);
    video->show();
    if(ui->buttonLoop->isChecked()) Play->setLoops(3);
    ui->toolButton->setChecked(true);
    Play->play();

}

QString MainWindow::convert_qint64_String(qint64 value)
{
    QTime time(value/3600,value/60,value);
    QString fomat="mm:ss";
    if (value>=3600) fomat="hh:mm:ss";
    return time.toString(fomat);
}

void MainWindow::positionChanged(qint64 position)
{
    ui->timePosition->setText(convert_qint64_String(position/1000));
    ui->timeSlider->setValue(position/1000);
    if(Play->duration()==position)
        Play_video(Path(1));

}


void MainWindow::on_buttonOpen_clicked()
{
    QString fileName= QFileDialog::getOpenFileName(this,tr("Chon video"),"Video",tr("MP4 file (*.MP4)"));
    if(!fileName.isNull())
        Play_video(fileName);
}


void MainWindow::on_actionServer_triggered(bool checked)
{
    if(checked){
        ui->stackedWidget->setCurrentIndex(0);
        ui->actionLive->setChecked(false);
        ui->actionVideo->setChecked(false);
        Server=new QTcpServer;
        Server->listen(QHostAddress::AnyIPv4,8081);
        connect(Server,&QTcpServer::pendingConnectionAvailable,this,&MainWindow::newConnect);
        addHistory("start");
    } else {
        Server->close();
        addHistory("stop");
    }
}


void MainWindow::on_actionVideo_triggered(bool checked)
{
    if(checked) {
        ui->stackedWidget->setCurrentIndex(1);
        Play_video("Video/"+List("Video/").value(0));
    }
}


void MainWindow::on_actionLive_triggered(bool checked)
{
    if(checked)    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_toolButton_clicked(bool checked)
{
    if(checked) Play->play();
    else Play->pause();
}


void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    audioOutput->setVolume((float)value/100);
}


void MainWindow::on_buttonVolume_toggled(bool checked)
{
    audioOutput->setVolume(checked);

}


void MainWindow::on_videoSpeed_valueChanged(int value)
{
    Play->setPlaybackRate((float)value/100);
}


void MainWindow::on_timeSlider_actionTriggered(int action)
{
    Play->setPosition(ui->timeSlider->value());
}


void MainWindow::on_beforeVideo_clicked()
{
    Play_video(Path(-1));
}


void MainWindow::on_NextVideo_clicked()
{
    Play_video(Path(1));
}


void MainWindow::on_videoTranslationLeft_clicked()
{
    Play->setPosition(Play->position()-10000);
}


void MainWindow::on_videoTranslationRight_clicked()
{
    Play->setPosition(Play->position()+10000);
}


void MainWindow::on_actionDataTransmission_triggered()
{
    ui->stackedWidget->setCurrentIndex(2);
}

