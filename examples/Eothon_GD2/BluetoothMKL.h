#ifndef BluetoothMKL_H___
#define BluetoothMKL_H___
#include "Arduino.h"
#include "Vietduino_DCmotor.h"

enum{
    MKL_BOT_F
};

class RobotBluetooth{
    public:
    Vietduino_DCmotor *pMotor_L;
    Vietduino_DCmotor *pMotor_R;

    uint16_t speed_L, speed_R;
    unsigned long timeOut;

    Stream * p_Serial;
    void setMotorTimeOut(unsigned long tTimeOut);
    void begin(Stream * tp_Serial, Vietduino_DCmotor *tpMotor_L, Vietduino_DCmotor *tpMotor_R);
    void loop();

    void Move_F();
    void Move_B();
    void Turn_L();
    void Turn_R();
    void Stop(); 
};

#endif