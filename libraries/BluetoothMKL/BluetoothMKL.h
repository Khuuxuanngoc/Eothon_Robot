#ifndef BluetoothMKL_H___
#define BluetoothMKL_H___
#include "Arduino.h"
#include "Vietduino_DCmotor.h"
#include "Vietduino_Task.h"

enum{
    MKL_BOT_F
};

class RobotBluetooth: public Vietduino_Task
{
    public:
    RobotBluetooth();
    ~RobotBluetooth(){}
    Vietduino_DCmotor *pMotor_L;
    Vietduino_DCmotor *pMotor_R;
    float scaleSpeed = 0.5;

    uint16_t speed_L, speed_R;
    unsigned long timeOut;

    Stream * p_Serial;
    void setMotorTimeOut(unsigned long tTimeOut);
    void begin(Stream * tp_Serial, Vietduino_DCmotor *tpMotor_L, Vietduino_DCmotor *tpMotor_R);
    void loop();
    static void run(Vietduino_Task * me);

    void Move_F();
    void Move_B();
    void Turn_L();
    void Turn_R();
    void Turn_FL();
    void Turn_FR();
    void Turn_BL();
    void Turn_BR();
    void Stop(); 
};

#endif