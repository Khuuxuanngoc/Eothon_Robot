/*
    GD2:
    - Robot di chuyen bang 4 dong co DC, su dung Driver CCS_SHB20 Mr.Linh
        https://hshop.vn/products/mach-dieu-khien-dong-co-dc-smart-h-bridge-cc-smart-ccs-shb20
    - Robot dieu khien qua Bluetooth

*/
#include "Vietduino_Manager_Priority.h"
#include "Vietduino_DCmotor.h"
#include "Eothon_Var.h"
#include "BluetoothMKL.h"

Vietduino_DCmotor mLeft( DIR_PIN_L, PWM_PIN_L);
Vietduino_DCmotor mRight( DIR_PIN_R, PWM_PIN_R);

RobotBluetooth myRobot;

void setup(){
    Serial.begin(9600);
    mLeft.setTogglePwm();
    mRight.setTogglePwm();
    myRobot.begin(&Serial,&mLeft,&mRight);

}

void loop(){
    VIETDUINO_UPDATE;

    myRobot.loop();
}