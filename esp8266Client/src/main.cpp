#include <Arduino.h>
#include<ESP8266WiFi.h>
#include <tcpClient.h>
#include <congTac.h>
#include <DNSServer.h>
#include <EEPROM.h>
#include <ESP8266WebServer.h>
#define soLuongCongTac 3
int port = 8081;
String SSID,Pass;
ESP8266WebServer server;
IPAddress IPserver(192,168,0,102);
tcpClient client(IPserver,port);
congTac trai,giua,phai;
bool setupDevice=false;
#define ID String(ESP.getChipId())
void receiveClient();
void setSwitch(congTac *Switch,int out,int in,bool state,String name,String &data);
void sendData(congTac *Switch);
bool connectWifi=false;
const char* html = R"html(<div>
<h1 style="font-size: 400%; color: blue; background-color: powderblue; border-radius: 25px; text-align: center;">Hey bro!</h1>
</div>
<div>
<h4>Ban nhap giup minh wifi de co the lay thoi gian thuc nhe <3</h4>
</div>
<form action="/action_page" style="font-size: 200%">
<p>Ten wifi nhap o day ne:</p>
<input style="height:55px; width:600px;font-size: 150%" type="text" name="SSID" required/>
<p>Pass wifi nhap o day ne:</p>
<input style="height:55px; width:600px;font-size: 150%" type="text" name="Pass" />
<input type="submit" style="color: white; font-size: 40px; border-radius: 5px; background-color: #008cba; border: none;" value="Save o day ne" />
</from>
<p>Luu y nhe: Vi yeu cau ket noi mang de lay thoi gian nen khi mat mang se yeu cau nhap mang moi hoac cho ket noi lai mang wifi truoc do. Thong cam cho minh vi dung tieng viet khong dau nhe.</p>
<p style="text-align: right; color: red; font-size: 150%;">Cam on nhieu nha <3</p>
)html";
struct infoWifi{
	String Ssid;
	String Psk;
};
bool connect(String name, String psk);
void setupServer();
void setup() {
	Serial.begin(115200);
    Serial.printf("err");
	infoWifi info;
	EEPROM.begin(sizeof(infoWifi));
	EEPROM.get(0,info);
	if(!info.Ssid.isEmpty())
		if(connect(info.Ssid,info.Psk)){
			SSID=info.Ssid;
			Pass=info.Psk;
		}
    while (!client.connectServer()){
        Serial.print(".");
        delay(500);
    }

}
void loop(){
	if(WiFi.status()!=WL_CONNECTED){
		setupServer();
		connectWifi=false;
		while(!connectWifi){
			WiFi.mode(WIFI_AP_STA);
			WiFi.begin(SSID,Pass);
			if (WiFi.status()==WL_CONNECTED)
				break;
    		server.handleClient();
		}
        ESP.restart();
	} else if(!setupDevice){
        client.registers();

        String dataSwitch="";
        bool getUpdate=false;

        if(client.exist(String(ID)))
            getUpdate=true;

        switch (soLuongCongTac){
            case 3:
                setSwitch(&trai,16,14,getUpdate,"trai",dataSwitch);
            case 2:
                setSwitch(&giua,5,12,getUpdate,"giua",dataSwitch);
            case 1:
                setSwitch(&phai,4,13,getUpdate,"phai",dataSwitch);
        }  

        if(!getUpdate){
            dataSwitch="Esp"+String(ID)+dataSwitch;
            client.createrDevice(dataSwitch);
        }
        setupDevice=true;
	} else {
        receiveClient();
        switch (soLuongCongTac){
            case 3:
                sendData(&trai);
            case 2:
                sendData(&giua);
            case 1:
                sendData(&phai);
        }
    }
}

void receiveClient(){
    String data=client.receive();
    if(!data.isEmpty()){
        String mode=data.substring(data.indexOf(":")+1,data.length());
        bool state=strcmp(mode.c_str(),"on")==0?true:false;
        if(data.startsWith("phai"))
            phai.setTrangThai(state);
        else if(data.startsWith("giua"))
            giua.setTrangThai(state);
        else if(data.startsWith("trai"))
            trai.setTrangThai(state);
    }
}

void setSwitch(congTac *Switch,int out,int in,bool state,String name,String &data){
    bool mode=state?client.value(String(ID),name,"switch"):false;
    Switch->init(out,in,mode,name);
    Switch->name=name;
    data+="{"+name+"(switch:off)"+"(name:"+name +")}";
}
void sendData(congTac *Switch){
    if(Switch->checkSwitch()){
        Switch->setTrangThai(!Switch->trangThai);
        String mode=Switch->trangThai?"on":"off";
        client.setData("setData:Esp"+String(ID)+"{"+Switch->name+"}switch:"+mode);
    }
}
bool connect(String name, String psk){
	WiFi.begin(name, psk);
    for(int numConnect=0;WiFi.status() != WL_CONNECTED&&numConnect<10;numConnect++) {
        delay(500);
		if(numConnect==9) return false;
    }
	SSID=name;
	Pass=psk;
	return true;
}
void handleSave() {
    String newSSID = server.arg("SSID"); 
    String newPass = server.arg("Pass"); 
    String s = "<p>Dai vuong cho 10s xem ket noi duoc wifi chua nhe. Neu den wifi co mau thi ket noi duoc roi nhe. Con neu khong co mau thi chua ket noi duoc dau dai vuong oi</p><a href='/'>Quay lai</a>";
    server.send(200, "text/html", s);
	if(connect(newSSID,newPass)) 
	{
		connectWifi=true;
		infoWifi info;
		info.Ssid=newSSID;
		info.Psk=newPass;
		EEPROM.put(0,info);
		EEPROM.commit();
		server.close();
	}
	else {
		connectWifi=false;
		setupServer();
	}
}

void handleRoot() {
    server.send(200, "text/html", html);
}

void handleNotFound() {
    server.send(404, "text/plain", "Khong tim thay trang Web");
}
void setupServer() {
   	WiFi.mode(WIFI_AP_STA);
    WiFi.softAP("Dong ho","12345678");
    server.on("/", handleRoot);
    server.on("/action_page", handleSave);
    server.onNotFound(handleNotFound);
    server.begin();
}