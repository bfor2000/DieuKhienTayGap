#ifndef tcpClient_h
#define tcpClient_h
#include <Arduino.h>
#include<ESP8266WiFi.h>
class tcpClient
{
private:
    IPAddress address;
    int port;
    WiFiClient client;
    bool getState(String event);
public:
    tcpClient(IPAddress diaChi,int cong);
    ~tcpClient();
    void registers();
    bool exist(String device);
    bool value(String device,String key,String varible);
    void createrDevice(String newDevice);
    bool connectServer();
    void setData(String command);
    String receive();
};

#endif