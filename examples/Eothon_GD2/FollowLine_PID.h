#ifndef _FollowLine_PID_H__
#define _FollowLine_PID_H__
#include "Arduino.h"
#include "Vietduino_DCmotor.h"

class FollowLine_PID: public Vietduino_Task
{
    public:
    FollowLine_PID();
    ~FollowLine_PID(){}
    Vietduino_DCmotor *pMotor_L;
    Vietduino_DCmotor *pMotor_R;

    uint16_t speed_L, speed_R;
    unsigned long timeOut;

    Stream * p_Serial;
    void begin(Stream * tp_Serial, Vietduino_DCmotor *tpMotor_L, Vietduino_DCmotor *tpMotor_R);
    void loop();
    static void run(Vietduino_Task * me);
};

#endif