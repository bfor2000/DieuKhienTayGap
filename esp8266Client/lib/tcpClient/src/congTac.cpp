#include <Arduino.h>
#include<congTac.h>
#include<ESP8266WiFi.h>
congTac::congTac(){}
void congTac::init(int8_t pinOutput,int8_t pinInput,bool state,String ten){
    output=pinOutput;
    input=pinInput;
    name=ten;
    trangThai=state;
    stateSwitch=false;
    pinMode(output,OUTPUT);
    pinMode(input,INPUT);
    digitalWrite(output,trangThai);
}
bool congTac::checkSwitch(){
    bool state=digitalRead(input);
    if(!stateSwitch&&state)
        stateSwitch=true;
    else if(stateSwitch&&!state){
        stateSwitch=false;
        return true;
    }
    return false;
}
void congTac::setTrangThai(bool state){
    digitalWrite(output,state);
    trangThai=state;
}