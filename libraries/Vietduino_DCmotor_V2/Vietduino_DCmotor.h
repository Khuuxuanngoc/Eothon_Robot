/**
 * File: Vietduino_DCmotor.h
 *
 * Author: Ngoc Khuu
 * Contact: xuanngoc1992@gmail.com
 * Copyright: 2018 Ngoc Khuu
 * Copying permission statement:

    Vietduino_DCmotor is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef __VIETDUINO_DC_MOTOR_H__
#define __VIETDUINO_DC_MOTOR_H__

#include "Arduino.h"
#include "Vietduino_Task.h"
#include "Vietduino_Io.h"
#include "Makerlabvn_I2C_Motor_Driver.h"

enum{
    _V_DIR_BACKWARD_ = 0,
    _V_DIR_FORWARD_
}dir_motor_state;

class Vietduino_DCmotor: public Vietduino_Task
{
 public:

        Vietduino_DCmotor(unsigned char _Port_Unobase_);
        Vietduino_DCmotor(unsigned char _dir_, unsigned char _speed_);

        Vietduino_DCmotor(Makerlabvn_I2C_Motor_Driver *tpDC_I2C_Driver, uint8_t tMKL_DC_index);

        virtual ~Vietduino_DCmotor(){}
	void forward(unsigned char s);
	void backward(unsigned char s);
        
        void forward(unsigned char s, unsigned long _runForMs_);
	void backward(unsigned char s, unsigned long _runForMs_);

        void stop();
        void write(int _speed__);
        void write(int _dir_, int _speed__);
        void write(int _dir_, int _speed__, unsigned long _runForMs_);
        void setTogglePwm();

        static void run(Vietduino_Task * me);
private:
        unsigned char dir;
        unsigned char pwm;
        unsigned char isTogglePwm;      // default True for IN1-IN2 L298

        unsigned char uc_Last_Dir_Val;
        unsigned char uc_Last_Pwm_Val;

        unsigned char _loopID_ = 0;

        unsigned long ul_timeRun;

        NK_IO_REG_TYPE myBit_d;
        volatile NK_IO_REG_TYPE *myReg_d;

        NK_IO_REG_TYPE myBit_s;
        volatile NK_IO_REG_TYPE *myReg_s;

        Makerlabvn_I2C_Motor_Driver *pDC_I2C_Driver;
        uint8_t MKL_DC_index = 0;
};

#endif //__DC_H__
