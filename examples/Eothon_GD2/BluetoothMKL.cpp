#ifndef BluetoothMKL_H___
#include "BluetoothMKL.h"

void RobotBluetooth::setMotorTimeOut(unsigned long tTimeOut){
    this->timeOut = tTimeOut;
}

void RobotBluetooth::begin(Stream * tp_Serial, Vietduino_DCmotor *tpMotor_L, Vietduino_DCmotor *tpMotor_R){
    this->p_Serial = tp_Serial;

    this->pMotor_L = tpMotor_L;
    this->pMotor_R = tpMotor_R;

    this->timeOut = 200; //200ms default
    this->speed_L = 200;
    this->speed_R = 200;
}

void RobotBluetooth::loop(){
    if(p_Serial->available()){
        char tempChar = p_Serial->read();

        Serial.println(tempChar);

        switch (tempChar)
        {
        case 'F':
            this->Move_F();
            break;
        
        case 'B':
            this->Move_B();
            break;
        
        case 'L':
            this->Turn_L();
            break;
        
        case 'R':
            this->Turn_R();
            break;
        
        case 'S':
            this->Stop();
            break;
        
        default:
            if((tempChar >= '0') and (tempChar <= '9')){
                this->speed_L = 255 * (tempChar - '0')/9;
                this->speed_R = 255 * (tempChar - '0')/9;
            }
            break;
        }
    }
}

void RobotBluetooth::Move_F(){
    this->pMotor_L->forward(this->speed_L, this->timeOut);
    this->pMotor_R->forward(this->speed_R, this->timeOut);
}

void RobotBluetooth::Move_B(){
    this->pMotor_L->backward(this->speed_L, this->timeOut);
    this->pMotor_R->backward(this->speed_R, this->timeOut);
}

void RobotBluetooth::Turn_L(){
    this->pMotor_L->backward(this->speed_L, this->timeOut);
    this->pMotor_R->forward(this->speed_R, this->timeOut);
}

void RobotBluetooth::Turn_R(){
    this->pMotor_L->forward(this->speed_L, this->timeOut);
    this->pMotor_R->backward(this->speed_R, this->timeOut);
}

void RobotBluetooth::Stop(){
    this->pMotor_L->stop();
    this->pMotor_R->stop();;
}

#endif