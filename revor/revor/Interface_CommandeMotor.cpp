//
//  Interface_CommandeMotor.cpp
//  revor
//

#include <stdio.h>
#include "Interface_CommandeMotor.h"

Interface_CommandeMotor::Interface_CommandeMotor()
{
    mpMotor = new DC_Motor();
    mpChuck = new Wii_Chuck();
}

Interface_CommandeMotor::~Interface_CommandeMotor()
{
    delete mpMotor;
    delete mpChuck;
}

// **************** Getteur / Setteur ****************

// Setteur
void Interface_CommandeMotor::setSpeed(const float aSpeed)
{
    mSpeed = aSpeed;
}

// Getteur
float Interface_CommandeMotor::getSpeed() const
{
    return mSpeed;
}

// **************** **************** ****************

void Interface_CommandeMotor::updateSpeed()
{
    if (mpChuck->readJoyX()>=mpChuck->readJoyY())
    {
        mSpeed = abs(mpChuck->readJoyX());
    }
    else
    {
        mSpeed = abs(mpChuck->readJoyY());
    }
}

void Interface_CommandeMotor::decode_Direction()
{
    // Neutral Area - Dead Zone
    if ()
    {
        
    }
    else if ()
    {
        
    }
    else if ()
    {
        
    }
    else if ()
    {
        
    }
    else
    {
        
    }
}








