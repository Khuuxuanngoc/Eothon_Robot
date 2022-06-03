/*
    GD2:
    - Robot di chuyen bang 4 dong co DC, su dung Driver CCS_SHB12 Mr.Linh
        https://hshop.vn/products/mach-dieu-khien-dong-co-dc-smart-h-bridge-cc-smart-ccs-shb20
    - Robot dieu khien qua Bluetooth

*/
#include "Vietduino_Manager_Priority.h"
#include "Vietduino_DCmotor.h"
#include "Eothon_Var.h"
// #include "BluetoothMKL.h"
#include "SoftwareSerial.h"
#include "FollowLine_PID.h"
#include "QTRSensors.h"

// Test Software Serial ok
// SoftwareSerial  sSerial(12,13);
// #define PWM_PIN_L   9
Makerlabvn_I2C_Motor_Driver myI2C_Driver;

Vietduino_DCmotor mLeft( &myI2C_Driver, 1);
Vietduino_DCmotor mRight( &myI2C_Driver, 0);

// Vietduino_DCmotor mLeft( DIR_PIN_L, PWM_PIN_L);
// Vietduino_DCmotor mRight( DIR_PIN_R, PWM_PIN_R);

// RobotBluetooth myRobot;
FollowLine_PID myRobot;
QTRSensors myFollowLineSensor;

double Setpoint, Input, Output;
double Kp=1, Ki=0.03, Kd=0.3;   // chay tot
double kArray[2][3]={{1,0.01,0.05},{1,0.003,0.3}};
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

void setup(){
    Serial.begin(9600);

    // Test Software Serial ok
    // sSerial.begin(9600);
    // myRobot.begin(&sSerial,&mLeft,&mRight); 

    mLeft.setTogglePwm();
    mRight.setTogglePwm();
    uint8_t tempSenPin[] = {A1, A2};
    myFollowLineSensor.setSensorPins((const uint8_t[]){A1, A2,}, 2);
    // myFollowLineSensor.setSensorPins(tempSenPin, 2);

    // myRobot.begin(&Serial, &mLeft, &mRight, &myFollowLineSensor);
    // myRobot.begin((Stream *)0,&mLeft,&mRight, &myFollowLineSensor);
    
    myI2C_Driver.begin();
    myRobot.begin(&myPID, &Serial, &mLeft, &mRight, &myFollowLineSensor);

    // myRobot.calibrateSensorInSecond(10, []{
    //     while(Serial.available()){
    //         char tempChar = Serial.read();
    //         Serial.print("tempchar: ");
    //         Serial.println(tempChar);

    //         if(tempChar == '1'){
    //             Serial.println("Stop calib");
    //             return true;
    //         }
    //     }
    //     return false;
    // });

}

void loop(){
    VIETDUINO_UPDATE;
    // myI2C_Driver.MA(1,255);
    // delay(2000);

    // myI2C_Driver.MA(1,127);
    // delay(2000);
    // myRobot.loop(); 
}