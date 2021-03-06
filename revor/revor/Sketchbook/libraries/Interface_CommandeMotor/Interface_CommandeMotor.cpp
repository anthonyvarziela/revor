//
//  Interface_CommandeMotor.cpp
//  revor
//

#include <stdio.h>
#include "Interface_CommandeMotor.h"

Interface_CommandeMotor::Interface_CommandeMotor():
mpMotor(NULL), //mpChuck(NULL),
mSpeed1(0), mSpeed2(0)
{
    Serial.println("Constructor Interface Commande -> Motor");
    mpMotor = new DC_Motor();
    mpChuck = new Wii_Chuck();
}

Interface_CommandeMotor::~Interface_CommandeMotor()
{
    delete mpMotor;
    delete mpChuck;
}

// init
void Interface_CommandeMotor::initialize()
{
    mpChuck->initialize();
    mpMotor->initializeAll();
}

// **************** Getteur / Setteur ****************

// Setteur
void Interface_CommandeMotor::setSpeed(const float aSpeed)
{
    mSpeed1 = aSpeed;
}

// Getteur
float Interface_CommandeMotor::getSpeed() const
{
    return mSpeed1;
}

// **************** **************** ****************

void Interface_CommandeMotor::updateSpeed()
{
    if (mpChuck->readJoyX()>=mpChuck->readJoyY())
    {
        mSpeed1 = 2*abs(mpChuck->readJoyX());
        mSpeed2 = mSpeed1-2*abs(mpChuck->readJoyY());
    }
    else
    {
        mSpeed1 = 2*abs(mpChuck->readJoyY());
        mSpeed2 = mSpeed1-2*abs(mpChuck->readJoyX());
    }
}

// Vitesse et direction moteurs
void Interface_CommandeMotor::decode_Direction()
{
    int ValueJoyX = mpChuck->readJoyX();
    int ValueJoyY = mpChuck->readJoyY();
    int neutralZone = 10;           // zone neutre
    int neutralNegativeZone = -10;  // zone neutre négative
    
    if (NULL != mpMotor)
    {
        // Bas-gauche
        if (((ValueJoyX) < (neutralNegativeZone)) &&
            ((ValueJoyY) < (neutralNegativeZone)))
        {
            mpMotor->run(1,mSpeed1,"BACKWARD");
            mpMotor->run(2,mSpeed2,"BACKWARD");
        }
        // Bas-droit
        else if (((ValueJoyX) > (neutralZone)) &&
                 ((ValueJoyY) < (neutralNegativeZone)))
        {
            mpMotor->run(1,mSpeed2,"BACKWARD");
            mpMotor->run(2,mSpeed1,"BACKWARD");    }
        // Haut-droit
        else if (((ValueJoyX) < (neutralNegativeZone)) &&
                 ((ValueJoyY) > (neutralZone)))
        {
            mpMotor->run(1,mSpeed2,"FORWARD");
            mpMotor->run(2,mSpeed1,"FORWARD");
        }
        // Haut-gauche
        else if (((ValueJoyX) > (neutralZone)) &&
                 ((ValueJoyY) > (neutralZone)))
        {
            mpMotor->run(1,mSpeed1,"FORWARD");
            mpMotor->run(2,mSpeed2,"FORWARD");
            
        }
        // demi-tour-gauche
        else if (((ValueJoyY) <= (neutralZone)) &&
                 ((ValueJoyY) >= (neutralNegativeZone)) &&
                 ((ValueJoyX) >= (neutralZone)))
        {
            mpMotor->run(1,mSpeed1,"FORWARD");
            mpMotor->run(2,0,"RELEASE");
        }
        // demi-tour-droit
        else if (((ValueJoyY) <= (neutralZone)) &&
                 ((ValueJoyY) >= (neutralNegativeZone)) &&
                 ((ValueJoyX) <= (neutralNegativeZone)))
        {
            mpMotor->run(1,0,"RELEASE");
            mpMotor->run(2,mSpeed1,"FORWARD");
        }
        // Avant
        else if (((ValueJoyX) <= (neutralZone)) &&
                 ((ValueJoyX) >= (neutralNegativeZone)) &&
                 ((ValueJoyY) >= (neutralZone)))
        {
            mpMotor->run(1,mSpeed1,"FORWARD");
            mpMotor->run(2,mSpeed1,"FORWARD");
            
        }
        // Arriere
        else if (((ValueJoyX) <= (neutralZone)) &&
                 ((ValueJoyX) >= (neutralNegativeZone)) &&
                 ((ValueJoyY) <= (neutralNegativeZone)))
        {
            mpMotor->run(1,mSpeed1,"BACKWARD");
            mpMotor->run(2,mSpeed2,"BACKWARD");
        }
        // Neutral Area - Dead Zone
        else
        {
            mpMotor->run(1,0,"RELEASE");
            mpMotor->run(2,0,"RELEASE");
        }
    }
}

void Interface_CommandeMotor::update()
{
    mpChuck->update();
    updateSpeed();
    decode_Direction();
}









