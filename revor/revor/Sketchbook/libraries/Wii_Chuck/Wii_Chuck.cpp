//
//  Wii_Chuck.cpp
//  Wii_Chuck
//


#include <stdio.h>
#include "Wii_Chuck.h"

Wii_Chuck::Wii_Chuck():
mCount(6)
{
    initialize();
    JoyCalibration();
}

void Wii_Chuck::initialize()
{
    Wire.begin();
    
    Wire.beginTransmission(ADRESS);	// transmit to device 0x52
    Wire.write (0x40);                  // sends memory address
    Wire.write (0x00);                  // sends memory address
    Wire.endTransmission();            // stop transmitting
    
    JoyCalibration();
    
    for (int i = 0; i<3;i++)
    {
        mAngles[i] = 0;
    }
    
}

void Wii_Chuck::JoyCalibration()
{
    update();
    
    mZero_JoyX = mJoyX;
    mZero_JoyY = mJoyY;
    
    mZero_JAccelX = (float)mStatus[2];
    mZero_JAccelY = (float)mStatus[3];
    mZero_JAccelZ = (float)mStatus[4];
    
}

void Wii_Chuck::update()
{
    Wire.requestFrom (ADRESS, 6);	// request data from nunchuck
    while (Wire.available ()) {
        // receive byte as an integer
        mStatus[mCount] = nunchuk_decode_byte(Wire.read()); //
        mCount++;
    }
    if (mCount > 5) {
        mbLastZ = mbBouttonZ;
        mbLastC = mbBouttonC;
        
        mJoyX = (mStatus[0]);
        mJoyY = (mStatus[1]);
        for (int i = 0; i < 3; i++)

            mAngles[i] = (mStatus[i+2] << 2) + ((mStatus[5] & (B00000011 << ((i+1)*2) ) >> ((i+1)*2)));
        
        mbBouttonZ = !( mStatus[5] & B00000001);
        mbBouttonC = !((mStatus[5] & B00000010) >> 1);
        write_zero(); // send the request for next bytes
        
    }

}

void Wii_Chuck::write_zero()
{
    mCount = 0;
    Wire.beginTransmission (ADRESS);	// transmit to device 0x52
    Wire.write (0x00);		// sends one byte
    Wire.endTransmission ();	// stop transmitting
}

byte Wii_Chuck::nunchuk_decode_byte(byte x)
{
    x = (x ^ 0x17) + 0x17;
    return x;
}

// Acc

float Wii_Chuck::readAccelX()
{
    return (float)mAngles[0] - mZero_JAccelX;
}

float Wii_Chuck::readAccelY()
{
    return (float)mAngles[1] - mZero_JAccelY;
}

float Wii_Chuck::readAccelZ()
{
    return (float)mAngles[2] - mZero_JAccelZ;
}

int Wii_Chuck::readJoyX()
{
    return mJoyX - mZero_JoyX;
}

int Wii_Chuck::readJoyY()
{
    return mJoyY - mZero_JoyY;
}


