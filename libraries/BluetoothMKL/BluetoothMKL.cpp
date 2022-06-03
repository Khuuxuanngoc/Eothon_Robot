#ifndef BluetoothMKL_H___
#include "BluetoothMKL.h"
#include "Vietduino_Manager_Priority.h"

enum{
    RB_FF = 'F',
    RB_BB = 'B',
    RB_L = 'L',
    RB_R = 'R',
    RB_FL = 'G',
    RB_FR = 'I',
    RB_BL = 'H',
    RB_BR = 'J'
};

RobotBluetooth::RobotBluetooth():Vietduino_Task(0, &RobotBluetooth::run){
    Vietduino_Manager_3.add(this);
}

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
        
        case RB_FL:
            this->Turn_FL();
            break;

        case RB_FR:
            this->Turn_FR();
            break;

        case RB_BL:
            this->Turn_BL();
            break;

        case RB_BR:
            this->Turn_BR();
            break;

        default:
            if((tempChar >= '0') and (tempChar <= '9')){
                this->speed_L = 255 * (tempChar - '0')/10;
                this->speed_R = 255 * (tempChar - '0')/10;
            }else if(tempChar == 'q'){
                this->speed_L = 255;
                this->speed_R = 255;
            }
            break;
        }
    }
}

void RobotBluetooth::run(Vietduino_Task *me){
    RobotBluetooth *p_tempMe = me;
    p_tempMe->loop();
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

void RobotBluetooth::Turn_FL(){
    this->pMotor_L->forward(this->speed_L * this->scaleSpeed, this->timeOut);
    this->pMotor_R->forward(this->speed_R, this->timeOut);
}

void RobotBluetooth::Turn_FR(){
    this->pMotor_L->forward(this->speed_L, this->timeOut);
    this->pMotor_R->forward(this->speed_R * this->scaleSpeed, this->timeOut);
}

void RobotBluetooth::Turn_BL(){
    this->pMotor_L->backward(this->speed_L * this->scaleSpeed, this->timeOut);
    this->pMotor_R->backward(this->speed_R, this->timeOut);
}

void RobotBluetooth::Turn_BR(){
    this->pMotor_L->backward(this->speed_L, this->timeOut);
    this->pMotor_R->backward(this->speed_R * this->scaleSpeed, this->timeOut);
}

void RobotBluetooth::Stop(){
    this->pMotor_L->stop();
    this->pMotor_R->stop();;
}

#endif