//
//  Interface_CommandeMotor.cpp
//  revor
//

#include <stdio.h>
#include "Interface_CommandeMotor.h"

Interface_CommandeMotor::Interface_CommandeMotor():
mpMotor(NULL), mpChuck(NULL),
mSpeed1(0), mSpeed2(0)
{
    //Serial.println("Constructor Interface Commande -> Motor");
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
    int JoyX = mpChuck->readJoyX();
    int JoyY = mpChuck->readJoyY();
    JoyX = map(JoyX, -129, 300, 0, 512);
    JoyY = map(JoyY, -121, 88, 0, 512);
    JoyX = constrain(JoyX, -255, 255);
    JoyY = constrain(JoyY, -255, 255);
    if (JoyX >= JoyY)
    {
        mSpeed1 = abs(JoyX);
        mSpeed2 = mSpeed1-abs(JoyY);
    }
    else
    {
        mSpeed1 = abs(JoyY);
        mSpeed2 = mSpeed1-abs(JoyX);
    }
}

// Vitesse et direction moteurs
void Interface_CommandeMotor::decode_Direction()
{
    int ValueJoyX = mpChuck->readJoyX();
    int ValueJoyY = mpChuck->readJoyY();
    int neutralZone = 5;           // zone neutre
    int neutralNegativeZone = -5;  // zone neutre négative
    
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
            mpMotor->run(2,mSpeed1,"BACKWARD");
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







