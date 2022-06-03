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

void FollowLine_PID::begin(PID *tpPID, Stream * tp_Serial, Vietduino_DCmotor *tpMotor_L, Vietduino_DCmotor *tpMotor_R, QTRSensors *tpQTR_Analog)
{
    this->p_Serial = tp_Serial;
    this->pQTR_Analog = tpQTR_Analog;

    this->pMotor_L = tpMotor_L;
    this->pMotor_R = tpMotor_R;

    this->timeOut = 200; //200ms default
    this->speed_L = 200;
    this->speed_R = 200;

    this->pPid = tpPID;
    this->pidInit();
}

void FollowLine_PID::loop(){
    if(this->p_Serial){
        if(this->p_Serial->available()){
            String tempString = this->p_Serial->readStringUntil('\n');
            int tempNum = tempString.toInt();
            this->p_Serial->println(tempNum);

            this->pMotor_L->write(tempNum);
        }
    }
}

void FollowLine_PID::calibrateSensorInSecond(unsigned long t_TimeInSecond, bool (*tBoolStopFunct)()){
    unsigned long tTimetoMili = t_TimeInSecond * 1000;
    unsigned long tLastTime = millis();

    while((millis() - tLastTime) < tTimetoMili){
        this->pQTR_Analog->calibrate();
        
        if(tBoolStopFunct) if(tBoolStopFunct()) break;
        delay(0);
    }
    
}

void FollowLine_PID::pidInit(){
    this->pPid->SetMode(AUTOMATIC);
    this->pPid->SetOutputLimits(-(this->speedMotorLimit), this->speedMotorLimit);
    this->pPid->mySetpoint = this->pQTR_Analog->getValueMaxFromSensor()/2;
}

void FollowLine_PID::getInputPID(uint8_t t_dir_){
    uint8_t tempSensorCount = this->pQTR_Analog->getSensorCount();
    uint16_t tempQTR_SensorValues[tempSensorCount];

    this->positionInput = this->pQTR_Analog->readLineBlack(tempQTR_SensorValues);
    if(_V_DIR_FORWARD_ == t_dir_) this->positionInput = (tempSensorCount * 1000) - this->positionInput;

    *this->pPid->myInput = this->positionInput;
}

void FollowLine_PID::controlPID(uint8_t t_dir_){
    double * tempMyOutput = this->pPid->myOutput;
    double tempPwmLimit = this->speedMotorLimit;
    int *tempSpeedL = this->speed_L;
    int *tempSpeedR = this->speed_R;

    int tempSpeedPwm_L = 0;
    int tempSpeedPwm_R = 0;

    this->getInputPID(t_dir_);
    this->pPid->Compute();

    *tempMyOutput = constrain(*tempMyOutput, -tempPwmLimit, tempPwmLimit);

    tempSpeedPwm_L = constrain(*tempSpeedL + (*tempMyOutput),-tempPwmLimit,tempPwmLimit);
    tempSpeedPwm_R = constrain(*tempSpeedR + (*tempMyOutput),-tempPwmLimit,tempPwmLimit);

    if(t_dir_ > 0){
        this->pMotor_L->write(tempSpeedPwm_L);
        this->pMotor_R->write(tempSpeedPwm_R);
    }else{
        this->pMotor_L->write(-tempSpeedPwm_L);
        this->pMotor_R->write(-tempSpeedPwm_R);
    }

}
#endif