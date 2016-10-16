//
//  Wii_Chuck.h
//  Wii_Chuck
//
//

/*
* This file is an adaptation of the code by these authors:
* Tod E. Kurt, http://todbot.com/blog/
*
* The Wii Nunchuck reading code is taken from Windmeadow Labs
* http://www.windmeadow.com/node/42
*/

#ifndef Wii_Chuck_h
#define Wii_Chuck_h

#include <Wire.h>
#include "Arduino.h"

// ********* Defaults Values *********

// Data
#define SDA PA0
// Clock
#define SLC PA1
//
#define ADRESS 0x52

//
#define ZEROX 510
#define ZEROY 490
#define ZEROZ 460

class Wii_Chuck
{
public:
    
    // Constructor
    Wii_Chuck();
    
    // ************ Initialization Firmware ************
    
    // Initialization
    void initialize();
    
    // *********** ************ *********** ************
    
    void JoyCalibration();
    
    //
    void update();
    
    // ************ Accesseur ************
    
    // Get the accel. values
    float readAccelX();
    float readAccelY();
    float readAccelZ();
    
    // Get Joy x,y values
    int readJoyX();
    int readJoyY();
    int readZeroJoyX();
    int readZeroJoyY();
    
    // Get buttons z,c values
    bool readButtonZ();
    bool readButtonC();
    
    // *********** ************ ***********
    
    //
    uint8_t nunchuk_decode_byte(uint8_t x);
    void write_zero();
    
    void dataDisplay();
    
private:
    
    //
    int mJoyX; int mJoyXrecalib;
    int mJoyY; int mJoyYrecalib;
    int mLastJoyX;
    int mLastJoyY;
    // From the calibration
    int mZero_JoyX;
    int mZero_JoyY;
    
    
    // Accel x,y,z axes
    int mAngles[3];
    float mZero_JAccelX;
    float mZero_JAccelY;
    float mZero_JAccelZ;
    
    uint8_t mStatus[6];		// array to store wiichuck output
    
    // Button z and c
    boolean mbBouttonZ, mbBouttonC;
    boolean mbLastZ, mbLastC;
    
};


#endif /* Wii_Chuck_h */
