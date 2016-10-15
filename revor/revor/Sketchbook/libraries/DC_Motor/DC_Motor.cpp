//
//  DC_Motor.cpp
//  DC_Motor_Firmware
//
//  Created by VARZIELA on 09.10.16.
//  Copyright © 2016 VARZIELA. All rights reserved.
//

#include "DC_Motor.hpp"

DC_Motor::DC_Motor()
{
    initializeAll();
}

DC_Motor::DC_Motor(int aMotor)
{
    initialize(aMotor);
}

void DC_Motor::initializeAll()
{
    setAllEnablePins();
    setAllControlPins();
    setSpeed(255);
}

void DC_Motor::setAllEnablePins()
{
    mEn1 = ENABLEPIN_MOTOR1;
    mEn2 = ENABLEPIN_MOTOR2;
    
    pinMode(mEn1, OUTPUT);
    pinMode(mEn2, OUTPUT);
}

void DC_Motor::setAllControlPins()
{
    mIn1 = CONTROLPIN1;
    mIn2 = CONTROLPIN2;
    mIn3 = CONTROLPIN3;
    mIn4 = CONTROLPIN4;
    
    pinMode(mIn1, OUTPUT);
    pinMode(mIn2, OUTPUT);
    pinMode(mIn3, OUTPUT);
    pinMode(mIn4, OUTPUT);
}

void DC_Motor::initialize(int aMotor)
{
    switch (aMotor)
    {
        case 1:
            mEn1 = ENABLEPIN_MOTOR1;
            mIn1 = CONTROLPIN1;
            mIn2 = CONTROLPIN2;
            setEnablePins(mEn1);
            setControlPins(mIn1, mIn2);
            break;
            
        case 2:
            mEn2 = ENABLEPIN_MOTOR2;
            mIn3 = CONTROLPIN3;
            mIn4 = CONTROLPIN4;
            setEnablePins(mEn2);
            setControlPins(mIn3, mIn4);
            break;
            
        default:
            break;
    }
}

void DC_Motor::setEnablePins(byte aEn)
{
    pinMode(aEn, OUTPUT);
}

void DC_Motor::setControlPins(byte aIn1, byte aIn2)
{
    pinMode(aIn1, OUTPUT);
    pinMode(aIn2, OUTPUT);
}

void DC_Motor::initialize(int aMotor, byte aEn, byte aIn1, byte aIn2)
{
    switch (aMotor)
    {
        case 1:
            mEn1 = aEn;
            mIn1 = aIn1;
            mIn2 = aIn2;
            setEnablePins(mEn1);
            setControlPins(mIn1, mIn2);
            break;
            
        case 2:
            mEn2 = aEn;
            mIn3 = aIn1;
            mIn4 = aIn2;
            setEnablePins(mEn2);
            setControlPins(mIn3, mIn4);
            break;
            
        default:
            break;
    }
}

void DC_Motor::setSpeed(int aSpeed)
{
    mSpeed = aSpeed;
}


/* ********** Reminder **********

  Motor Logic
  ______________________________
 |          |         |         |
 |          |   In1   |   In2   |
 |__________|_________|_________|
 |          |         |         |
 | Forward  |    0    |    1    |
 |__________|_________|_________|
 |          |         |         |
 | Backward |    1    |    0    |
 |__________|_________|_________|
 |          |         |         |
 | BREAK    |  1 or 0 | 1 or 0  |
 |__________|_________|_________|
 
*/
void DC_Motor::controlRevor_Motor(int aSpeed, bool bIn1, bool bIn2) //, bool bIn3, bool bIn4)
{
    setSpeed(aSpeed);
    
    // Enable - Speed - PWM
    analogWrite(mEn1, mSpeed);
    // analogWrite(mEn2, mSpeed);
    
    // Motor 1
    digitalWrite(mIn1, bIn1);
    digitalWrite(mIn2, bIn2);
    
    /*// Motor 2
    digitalWrite(mIn3, bIn3);
    digitalWrite(mIn4, bIn4);*/
}


