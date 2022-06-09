/*
    GD2:
    - Robot di chuyen bang 4 dong co DC, su dung Driver CCS_SHB12 Mr.Linh
        https://hshop.vn/products/mach-dieu-khien-dong-co-dc-smart-h-bridge-cc-smart-ccs-shb20
    - Robot dieu khien qua Bluetooth

*/

#define USE_BLACK_CAT_ROBOT     0
// #define USE_EOTHON_ROBOT     1

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
//=====================VARIABLE=======================================================
// RobotBluetooth myRobot;
FollowLine_PID myRobot;
QTRSensors myFollowLineSensor;

double Setpoint, Input, Output;
double Kp=1, Ki=0.03, Kd=0.3;   // chay tot
double kArray[2][3]={{1,0.01,0.05},{1,0.003,0.3}};
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);
//=====================END VARIABLE=======================================================

#if defined(USE_BLACK_CAT_ROBOT) //====================
Makerlabvn_I2C_Motor_Driver myI2C_Driver;

Vietduino_DCmotor mLeft( &myI2C_Driver, 1);
Vietduino_DCmotor mRight( &myI2C_Driver, 0);

void MotorInit(){
    // Use MKL I2C Motor Driver
    myI2C_Driver.begin();

}

void SensorFollowLineInit(){
    uint8_t tempSenPin[] = {A1, A2, A3};
    myFollowLineSensor.setTypeAnalog();
    myFollowLineSensor.setSensorPins(tempSenPin, sizeof(tempSenPin));
    // myFollowLineSensor.setSensorPins((const uint8_t[]){A1, A2}, 2);
}

void PID_Init(){
    // Kp = 0.1;
    // Ki = 0;
    // Kd = 0.05;

    Kp = 90; // Y22M06D09
    Ki = 10;
    Kd = 30;

    myPID.SetTunings(Kp, Ki, Kd);
}

#elif defined(USE_EOTHON_ROBOT)//====================

Vietduino_DCmotor mLeft( DIR_PIN_L, PWM_PIN_L);
Vietduino_DCmotor mRight( DIR_PIN_R, PWM_PIN_R);

void MotorInit(){
    // Used for Driver CCS_SHB12. Comment to use for L298
    mLeft.setTogglePwm();
    mRight.setTogglePwm();

}

void SensorFollowLineInit(){
    uint8_t tempSenPin[] = {SENSOR_HALL_PIN_L, SENSOR_HALL_PIN_R};
    myFollowLineSensor.setTypeAnalog();
    myFollowLineSensor.setSensorPins(tempSenPin, sizeof(tempSenPin));
    // myFollowLineSensor.setSensorPins((const uint8_t[]){A1, A2}, 2);
}

#endif//================================================



void setup(){
    Serial.begin(9600);
    Serial.println("Start");

    // Test Software Serial ok
    // sSerial.begin(9600);
    // myRobot.begin(&sSerial,&mLeft,&mRight); 

    MotorInit();
    SensorFollowLineInit();
    PID_Init();
    // myFollowLineSensor.setSensorPins(tempSenPin, 2);

    // myRobot.begin(&Serial, &mLeft, &mRight, &myFollowLineSensor);
    // myRobot.begin((Stream *)0,&mLeft,&mRight, &myFollowLineSensor);
    
    myRobot.begin(&myPID, &Serial, &mLeft, &mRight, &myFollowLineSensor);

    myRobot.calibrateSensorInSecond(10, []{
        while(Serial.available()){
            char tempChar = Serial.read();
            Serial.print("tempchar: ");
            Serial.println(tempChar);

            if(tempChar == '1'){
                Serial.println("Stop calib");
                return true;
            }
        }
        return false;
    });

    Serial.println(F("Calib Done"));
}

void loop(){
    VIETDUINO_UPDATE;
    // myI2C_Driver.MA(1,255);
    // delay(2000);

    // myI2C_Driver.MA(1,127);
    // delay(2000);
    // myRobot.loop(); 
}