#ifndef _FollowLine_PID_H__
#include "FollowLine_PID.h"
#include "Vietduino_Manager_Priority.h"
#include "FollowLine_Debug_Var.h"

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
    this->speed_L = 0;
    this->speed_R = 0;
    this->speedMotorLimit = 200;

    this->pPid = tpPID;
    this->pidInit();
}

void FollowLine_PID::loop(){
    static int numFlag = 0;
    if(this->p_Serial){
        if(this->p_Serial->available()){
            String tempString = this->p_Serial->readStringUntil('\n');
            int tempNum = tempString.toInt();
            this->p_Serial->println(tempNum);
            
            // this->pMotor_L->forward(tempNum,3000);
            // this->pMotor_R->forward(tempNum,2000);
            if(tempString.indexOf("p") > -1){
                double tempKp = this->pPid->GetKp();
                double tempKi = this->pPid->GetKi();
                double tempKd = this->pPid->GetKd();

                tempKp = tempString.toFloat();
                DEBUG_SERIAL_CMD_T(F("Set kp"));
                DEBUG_SERIAL_CMD_T(tempKp);
                DEBUG_SERIAL_CMD_T(tempKi);
                DEBUG_SERIAL_CMD_LN(tempKd);
                this->pPid->SetTunings(tempKp, tempKi, tempKd);
            }else if(tempString.indexOf("i") > -1){
                double tempKp = this->pPid->GetKp();
                double tempKi = this->pPid->GetKi();
                double tempKd = this->pPid->GetKd();

                tempKi = tempString.toFloat();
                DEBUG_SERIAL_CMD_T(F("Set ki"));
                DEBUG_SERIAL_CMD_T(tempKp);
                DEBUG_SERIAL_CMD_T(tempKi);
                DEBUG_SERIAL_CMD_LN(tempKd);
                this->pPid->SetTunings(tempKp, tempKi, tempKd);
            }else if(tempString.indexOf("d") > -1){
                double tempKp = this->pPid->GetKp();
                double tempKi = this->pPid->GetKi();
                double tempKd = this->pPid->GetKd();

                tempKd = tempString.toFloat();
                DEBUG_SERIAL_CMD_T(F("Set kd"));
                DEBUG_SERIAL_CMD_T(tempKp);
                DEBUG_SERIAL_CMD_T(tempKi);
                DEBUG_SERIAL_CMD_LN(tempKd);
                this->pPid->SetTunings(tempKp, tempKi, tempKd);
            }else if(tempString.indexOf("s") > -1){
                this->speed_L = tempString.toInt();
                this->speed_R = tempString.toInt();

                // tempKd = tempString.toFloat();
                DEBUG_SERIAL_CMD_T(F("Set speed"));
                DEBUG_SERIAL_CMD_T(this->speed_L);
                DEBUG_SERIAL_CMD_LN(this->speed_R);
            }else{
                numFlag = tempNum;
            }
            
        }
    }

    if(numFlag == 1){
        controlPID(FollowLine_PID_FORWARD);  
    } else if(numFlag == 2){
        controlPID(FollowLine_PID_BACKWARD);  
    }else  if(numFlag == 3){
        this->pMotor_L->stop();
        this->pMotor_R->stop();
    }
    // this->setPeriodMs(5);

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
    // int tempGetSetpointValue = this->pQTR_Analog->getValueMaxFromSensor()/2;
    int tempGetSetpointValue = 0; //knx add y22m06d09 
    this->pPid->SetMode(AUTOMATIC);
    this->pPid->SetOutputLimits(-(this->speedMotorLimit)*2, this->speedMotorLimit * 2);
    *this->pPid->mySetpoint = tempGetSetpointValue;
    
    // int tempMySetpoint = *this->pPid->mySetpoint;
    // Serial.println(tempGetSetpointValue);
    // Serial.println(tempMySetpoint);
}

void FollowLine_PID::getInputPID(uint8_t t_dir_){
    uint8_t tempSensorCount = this->pQTR_Analog->getSensorCount();
    uint16_t tempQTR_SensorValues[tempSensorCount];
    int tempMaxValueFromQTR = this->pQTR_Analog->getValueMaxFromSensor();

    this->positionInput = this->pQTR_Analog->readLineBlack(tempQTR_SensorValues);
    if(_V_DIR_FORWARD_ == t_dir_) this->positionInput = tempMaxValueFromQTR - this->positionInput;

    *this->pPid->myInput = (double)this->positionInput - (double)(tempMaxValueFromQTR/2);
    // *this->pPid->myInput = this->positionInput;
    DEBUG_RAW_QTR_VALUE_LN(F("DEBUG_RAW_QTR_VALUE_LN"));
    DEBUG_RAW_QTR_VALUE_T(tempSensorCount);
    DEBUG_RAW_QTR_VALUE_T(tempQTR_SensorValues[0]);
    DEBUG_RAW_QTR_VALUE_T(tempQTR_SensorValues[1]);
    DEBUG_RAW_QTR_VALUE_T(*this->pPid->myInput);
    DEBUG_RAW_QTR_VALUE_LN(this->positionInput);
    // Serial.print(tempSensorCount);Serial.print("\t");
    // Serial.print(tempQTR_SensorValues[0]);Serial.print("\t");
    // Serial.print(tempQTR_SensorValues[1]);Serial.print("\t");
    // Serial.println(this->positionInput);
}

void FollowLine_PID::controlPID(uint8_t t_dir_){
    static double tempLastInput = 0;
    double * tempMyOutput = this->pPid->myOutput;
    double * tempMyInput = this->pPid->myInput;
    double * tempSetPoint = this->pPid->mySetpoint;
    double tempPwmLimit = this->speedMotorLimit;
    double tempErr = 15;
    double *tempSpeedL = &this->speed_L;
    double *tempSpeedR = &this->speed_R;
    // double *tempSpeedL = 0;
    // double *tempSpeedR = 0;

    double tempSpeedPwm_L = 0;
    double tempSpeedPwm_R = 0;

    if(millis() - this->lastTimeComputePID >= 5){
        this->lastTimeComputePID = millis();
        this->getInputPID(t_dir_);
        // if(tempLastInput == *tempMyInput){
        //     return;
        // }
        // tempLastInput = *tempMyInput;

        if((*tempMyInput <= (*tempSetPoint + tempErr)) && (*tempMyInput >= (*tempSetPoint - tempErr))){
            *tempMyInput = *tempSetPoint;

            tempSpeedPwm_L = *tempSpeedL;
            tempSpeedPwm_R = *tempSpeedR;
        }else{
            if(this->pPid->Compute()){
                // *tempMyOutput = constrain(*tempMyOutput, -tempPwmLimit, tempPwmLimit);
                double d_tempOutput = *tempMyOutput;
                // d_tempOutput = constrain(d_tempOutput,-tempPwmLimit,tempPwmLimit);
                tempSpeedPwm_L = constrain(*tempSpeedL + d_tempOutput,-tempPwmLimit,tempPwmLimit);
                tempSpeedPwm_R = constrain(*tempSpeedR - d_tempOutput,-tempPwmLimit,tempPwmLimit);
            }
        }
        

        if(t_dir_ > 0){
            this->pMotor_L->write(tempSpeedPwm_L);
            this->pMotor_R->write(tempSpeedPwm_R);
            DEBUG_RAW_PID_VALUE_T(F("DEBUG_RAW_PID_VALUE_LN 1"));
            DEBUG_RAW_PID_VALUE_T(*tempSetPoint);
            DEBUG_RAW_PID_VALUE_T(*tempMyInput);
            DEBUG_RAW_PID_VALUE_T(*tempMyOutput);
            DEBUG_RAW_PID_VALUE_T(d_tempOutput);
            DEBUG_RAW_PID_VALUE_T(tempSpeedPwm_L);
            DEBUG_RAW_PID_VALUE_LN(tempSpeedPwm_R);

        }else{
            this->pMotor_L->write(-tempSpeedPwm_L);
            this->pMotor_R->write(-tempSpeedPwm_R);
            DEBUG_RAW_PID_VALUE_T(F("DEBUG_RAW_PID_VALUE_LN 0"));
            DEBUG_RAW_PID_VALUE_T(*tempSetPoint);
            DEBUG_RAW_PID_VALUE_T(*tempMyInput);
            DEBUG_RAW_PID_VALUE_T(*tempMyOutput);
            DEBUG_RAW_PID_VALUE_T(d_tempOutput);
            DEBUG_RAW_PID_VALUE_T(tempSpeedPwm_L);
            DEBUG_RAW_PID_VALUE_LN(tempSpeedPwm_R);
        }
    }
    

    
}
#endif