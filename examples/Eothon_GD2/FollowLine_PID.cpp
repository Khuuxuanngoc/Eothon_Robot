#ifndef _FollowLine_PID_H__
#include "FollowLine_PID.h"
#include "Vietduino_Manager_Priority.h"

FollowLine_PID::FollowLine_PID():Vietduino_Task(0, &FollowLine_PID::run){
    Vietduino_Manager_3.add(this);
}

void FollowLine_PID::run(Vietduino_Task * me){
    FollowLine_PID *p_tempMe = me;
    p_tempMe->loop();
}

void FollowLine_PID::begin(Stream * tp_Serial, Vietduino_DCmotor *tpMotor_L, Vietduino_DCmotor *tpMotor_R)
{
    this->p_Serial = tp_Serial;

    this->pMotor_L = tpMotor_L;
    this->pMotor_R = tpMotor_R;

    this->timeOut = 200; //200ms default
    this->speed_L = 200;
    this->speed_R = 200;
}

void FollowLine_PID::loop(){
    if(this->p_Serial->available()){
        String tempString = this->p_Serial->readStringUntil('\n');
        int tempNum = tempString.toInt();
        this->p_Serial->println(tempNum);

        this->pMotor_L->write(tempNum);
    }
}

#endif