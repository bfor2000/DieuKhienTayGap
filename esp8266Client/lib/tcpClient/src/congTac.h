#ifndef congTac_h
#define congTac_h
#include <Arduino.h>
#include<ESP8266WiFi.h>
class congTac{
    private:
    int8_t output;
    int8_t input;
    bool stateSwitch;
    public:
    String name;
    bool trangThai;
    congTac();
    void init(int8_t pinOutput,int8_t pinInput,bool state,String ten);
    bool checkSwitch();
    void setTrangThai(bool state);
};
#endif