//
//  DC_Motor.hpp
//  DC_Motor_Firmware
//

#ifndef DC_Motor_hpp
#define DC_Motor_hpp

#include <stdio.h>
#include "Arduino.h"

// ********* Defaults Values *********

// PWM Pins
#define ENABLEPIN_MOTOR1 3
#define ENABLEPIN_MOTOR2 5
// Motor 1
#define CONTROLPIN1 2
#define CONTROLPIN2 4
// Motor 2
#define CONTROLPIN3 7
#define CONTROLPIN4 8

class DC_Motor
{
public:
    
    // Constructor
    DC_Motor();
    DC_Motor(int);
    DC_Motor(int,byte,byte,byte);
    
    // **************** Initialization ****************
    
    // Initialization All Pins/Inputs ...
    void initializeAll();
    void setAllEnablePins();
    void setAllControlPins();
    
    // Initialization 1 argument - With value by default
    void initialize(int);
    void setEnablePins(byte);
    void setControlPins(byte,byte);
    
    // Initialization - With Pin value choosen by the user
    void initialize(int,byte,byte,byte);
    
    // *********** ************ *********** ************
    
    void displayInitialization();
    
    //void setDelay(int);
    void setSpeed(int);
    
    void controlRevor_Motor(int,bool,bool,bool,bool);
    
private:
    
    int mSpeed; // PWM motor speed
    
    // enable pins
    byte mEn1;
    byte mEn2;
    
    // Control Pins
    byte mIn1;
    byte mIn2;
    byte mIn3;
    byte mIn4;
    
};

#endif /* DC_Motor_hpp */
