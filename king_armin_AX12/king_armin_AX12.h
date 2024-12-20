#include "Arduino.h"
class AX12{
private:
    HardwareSerial *varSerial;
    long BoundRated;
public:
    AX12(HardwareSerial &Serialport , long boundRated){
        varSerial = &Serialport;
        BoundRated = boundRated;
    }
    void Init();
    void LED(int id,int value);
    void set_speed(int id,int speed);
    void setAngleLimit(int id, int cwLimit, int ccwLimit);
    void setWheelMode(int id);
    void setJointMode(int id, int cwLimit, int ccwLimit);
    void set_degree(int id, int degree, int speed);
    void torque(int id,int Value) ;
};
