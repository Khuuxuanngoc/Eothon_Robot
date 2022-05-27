/*
    Simple_Test_DC_Motor

    - Test on Driver CCS_SHB12
        https://hshop.vn/products/mach-dieu-khien-dong-co-dc-smart-h-bridge-cc-smart-ccs-shb20
*/
#include "Vietduino_Manager_Priority.h"
#include "Vietduino_DCmotor.h"

#define PWM_PIN_FL  3
#define DIR_PIN_FL  2
Vietduino_DCmotor M_FL( DIR_PIN_FL, PWM_PIN_FL);

void setup(){
    M_FL.setTogglePwm(); // Comment this code when use L298
}

void loop(){
    VIETDUINO_UPDATE;

    M_FL.write(1, 255);
    delay(2000);

    M_FL.write(1, 0);
    delay(2000);

    M_FL.write(0, 255);
    delay(2000);

    M_FL.write(0, 0);
    delay(2000);

    M_FL.write(1, 127,2000);
    delay(4000);

    M_FL.write(1, 0);
    delay(2000);

    M_FL.write(0, 127,2000);
    delay(4000);

    M_FL.write(0, 0);
    delay(2000);
}