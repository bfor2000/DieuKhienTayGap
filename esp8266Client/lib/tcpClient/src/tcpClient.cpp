#include "tcpClient.h"
#include <Arduino.h>
#include<ESP8266WiFi.h>

tcpClient::tcpClient(IPAddress diaChi,int cong){
    address=diaChi;
    port=cong;
}
bool tcpClient::connectServer(){
    return client.connect(address,port);
}
bool tcpClient::exist(String device){
    String command="Device:Esp"+device;
    client.write(command.c_str());
    delay(1000);
    String data=receive();
    return strcmp(data.c_str(),"exist")==0?true:false;
}
void tcpClient::registers(){
    client.write("register:0");
}
void tcpClient::createrDevice(String newDevice){
    String command="Creater device:"+newDevice+"congtac";
    client.write(command.c_str());
}

bool tcpClient::value(String device,String key,String varible){
    String command="getData:Esp"+device+"{"+key+"}"+varible;
    client.write(command.c_str());
    delay(1000);
    String data=receive();
    return strcmp(data.c_str(),"on")==0?true:false;
}
tcpClient::~tcpClient(){}

void tcpClient::setData(String command){
    Serial.println(command);
    client.write(command.c_str());
}

bool tcpClient::getState(String event){
    String command=receive();
    return (command==event?true:false);
}

String tcpClient::receive(){
    String dataReceive="";
    while (client.available())
        dataReceive+=(char)client.read();
    return dataReceive;
}