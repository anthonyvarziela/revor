//
//  DC_Motor.cpp
//  DC_Motor_Firmware
//

#include "DC_Motor.hpp"

DC_Motor::DC_Motor():
mEn1(0), mEn2(0),
mIn1(0), mIn2(0), mIn3(0),mIn4(0)
{
    Serial.println("Default Constructor -> MotorFirmware");
}

void DC_Motor::initializeAll()
{
    setAllEnablePins();
    setAllControlPins();
    setSpeed(1,0);
    setSpeed(2,0);
}

void DC_Motor::setAllEnablePins()
{
    mEn1 = ENABLEPIN_MOTOR1;
    mEn2 = ENABLEPIN_MOTOR2;
    
    pinMode(mEn1, OUTPUT);
    pinMode(mEn2, OUTPUT);
    
    run(1,0,"RELEASE");
    run(2,0,"RELEASE");
}

// By default
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

void DC_Motor::setSpeed(int aMotor, int aSpeed)
{
    switch (aMotor)
    {
        case 1:
            mSpeed1 = aSpeed;
            break;
            
        case 2:
            mSpeed2 = aSpeed;
            break;
            
        default:
            break;
    }
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
void DC_Motor::run(int aMotor, int aSpeed, char* asCmd)
{
    bool bIn1 = 0; bool bIn2 = 0;
    
    interfaceDisplayObject();
    
    if (strcmp(asCmd,"FORWARD"))
    {
        bIn1 = LOW;
        bIn2 = HIGH;
    }
    else if (strcmp(asCmd,"BACKWARD"))
    {
        bIn1 = HIGH;
        bIn2 = LOW;
    }
    else
    {
        bIn1 = LOW;
        bIn2 = LOW;
    }
    
    switch (aMotor) {
        case 1:
            
            // Motor 1
            digitalWrite(mIn1, bIn1);
            digitalWrite(mIn2, bIn2);
            // Enable - Speed - PWM
            analogWrite(mEn1, aSpeed);
            break;
            
        case 2:
            
            // Motor 1
            digitalWrite(mIn3, bIn1);
            digitalWrite(mIn4, bIn2);
            
            // Enable - Speed - PWM
            analogWrite(mEn2, aSpeed);
            break;
            
        default:
            break;
    }
}

void DC_Motor::interfaceDisplayObject()
{
    Serial.println("*************** Object Interface : ***************");
    Serial.print("Speed : ("); Serial.print(mSpeed1);
    Serial.print(","); Serial.print(mSpeed2); Serial.print(")");
    Serial.println("");
    
    Serial.println("Motor 1 :");
    Serial.print("PinEnable : "); Serial.println(mEn1);
    Serial.print("PinControls ("); Serial.print(mIn1);
    Serial.print(","); Serial.print(mIn2); Serial.print(")");
    Serial.println("");
    
    Serial.println("Motor 2 :");
    Serial.print("PinEnable : "); Serial.print(mEn2);
    Serial.print("PinControls : ("); Serial.print(mIn3);
    Serial.print(","); Serial.print(mIn4); Serial.print(")");
    Serial.println("");
    
}


