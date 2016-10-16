//
//  Wii_Chuck.cpp
//  Wii_Chuck
//


#include <stdio.h>
#include "Wii_Chuck.h"

Wii_Chuck::Wii_Chuck():
mJoyX(0), mJoyY(0),
mLastJoyX(1), mLastJoyY(1),
mZero_JoyX(0), mZero_JoyY(0),
mZero_JAccelX(0), mZero_JAccelY(0), mZero_JAccelZ(0),
mbBouttonZ(false), mbBouttonC(false),
mbLastZ(false), mbLastC(false)
{
    for (int i = 0; i<3; i++)
    {
        mAngles[i] = 0;
    }
    
    for (int i = 0; i < 6 ; i++)
    {
        mStatus[i] = 0x00;
    }
    //initialize();
}

void Wii_Chuck::initialize()
{
    Wire.begin();
    /*
    // Official NunChuck
    Wire.beginTransmission(0x52);	// transmit to device 0x52
    Wire.write (0x40);                  // sends memory address
    Wire.write (0x00);                  // sends memory address
    Wire.endTransmission();            // stop transmitting
    */
    // No Official NunChuck
    Wire.beginTransmission (ADRESS); // transmit to device 0x52
    Wire.write (0xF0); // sends memory address
    Wire.write (0x55); // sends sent a zero.
    Wire.endTransmission (); // stop transmitting
    
    Wire.beginTransmission (ADRESS); // transmit to device 0x52
    Wire.write (0xFB); // sends memory address
    Wire.write (0x00); // sends sent a zero.
    Wire.endTransmission (); // stop transmitting
    
    while (mLastJoyX != mZero_JoyX &&
           mLastJoyY != mZero_JoyY)
    {
        JoyCalibration();
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
    //Serial.println(mZero_JoyY);
    //Serial.println(mZero_JoyX);

}

void Wii_Chuck::update()
{
    int counter = 0;
    Wire.requestFrom (ADRESS, 6);	// request data from nunchuck
    while (Wire.available ())
    {
        // receive byte as an integer
        mStatus[counter] = nunchuk_decode_byte(Wire.read()); //
        counter++;
    }
    
    if (counter >= 5)
    {
        mbLastZ = mbBouttonZ;
        mbLastC = mbBouttonC;
        
        // Save previous value
        mLastJoyX = mJoyX;
        mLastJoyY = mJoyY;
        
        // Update Actu value
        mJoyX = mStatus[0];
        mJoyY = mStatus[1];
        
        for (int i = 0; i < 3; i++)

            mAngles[i] = (mStatus[i+2] << 2) + ((mStatus[5] & (B00000011 << ((i+1)*2) ) >> ((i+1)*2)));
        
        mbBouttonZ = !( mStatus[5] & B00000001);
        mbBouttonC = !((mStatus[5] & B00000010) >> 1);
        
        write_zero(); // send the request for next bytes

        mJoyXrecalib = mJoyX - mZero_JoyX;
        mJoyYrecalib = mJoyY - mZero_JoyY;
        dataDisplay();
    }
    counter = 0;
}

void Wii_Chuck::write_zero()
{
    Wire.beginTransmission (0x52);	// transmit to device 0x52
    Wire.write (0x00);		// sends one byte
    Wire.endTransmission ();	// stop transmitting
}

uint8_t Wii_Chuck::nunchuk_decode_byte(uint8_t x)
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
    return mJoyXrecalib;
}

int Wii_Chuck::readJoyY()
{
    return mJoyYrecalib;
}

int Wii_Chuck::readZeroJoyX()
{
    return mZero_JoyX;
}

int Wii_Chuck::readZeroJoyY()
{
    return mZero_JoyY;
}

void Wii_Chuck::dataDisplay()
{
    Serial.print (mJoyXrecalib);
    Serial.print ("\t");
    Serial.print (mJoyYrecalib);
    Serial.print ("\t");
    
    Serial.print ("Button Z : ");
    Serial.print (mbBouttonZ);
    Serial.print ("\t");
    Serial.println();
    /*
    Serial.print (accel_x_axis, DEC);
    Serial.print ("\t");
    Serial.print (accel_y_axis, DEC);
    Serial.print ("\t");
    Serial.print (accel_z_axis, DEC);
    Serial.print ("\t");
    Serial.print (z_button, DEC);
    Serial.print ("\t");
    Serial.print (c_button, DEC);
    Serial.print ("\r\n");
    */
}


