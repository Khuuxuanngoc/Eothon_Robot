#ifndef _FollowLine_PID_H__
#define _FollowLine_PID_H__
#include "Arduino.h"
#include "Vietduino_DCmotor.h"
#include "QTRSensors.h"
#include "PID_v1.h"

enum{
    FollowLine_PID_BACKWARD = 0,
    FollowLine_PID_FORWARD  = 1
};

class FollowLine_PID: public Vietduino_Task
{
    public:
    FollowLine_PID();
    ~FollowLine_PID(){}
    Vietduino_DCmotor *pMotor_L;
    Vietduino_DCmotor *pMotor_R;

    double speedMotorLimit;

    QTRSensors *pQTR_Analog;
    uint16_t positionInput;

    PID *pPid;

    double speed_L, speed_R;
    unsigned long timeOut;
    unsigned long lastTimeComputePID = 0;

    Stream * p_Serial;
    void begin(PID *tpPID, Stream * tp_Serial, Vietduino_DCmotor *tpMotor_L, Vietduino_DCmotor *tpMotor_R, QTRSensors *tpQTR_Analog);
    void loop();
    static void run(Vietduino_Task * me);

    // FollowLine code zone:
    void calibrateSensorInSecond(unsigned long t_TimeInSecond, bool (*tBoolStopFunct)() = 0);

    void pidInit();
    void getInputPID(uint8_t t_dir_);
    void controlPID(uint8_t t_dir_);



};

#endif