//
// revor
//
// Description of the project
// Developed with [embedXcode](http://embedXcode.weebly.com)
//
// Author 		MrRevor
//
//
// Date			15.10.16 19:03
// Version		<#version#>
//
// Copyright	© MrRevor, 2016
// Licence		<#licence#>
//
// See         ReadMe.txt for references
//


#include "Arduino.h"
// Set parameters


// Include application, user and local libraries
#include "Wii_Chuck.h"
#include "DC_Motor.hpp"
#include "Interface_CommandeMotor.h"

// Prototypes

// Define variables and constants
Interface_CommandeMotor oCmd = Interface_CommandeMotor();
//Wii_Chuck ff = Wii_Chuck();

// Add setup code
void setup()
{
    Serial.begin(115200);
    delay(100);
    oCmd.initialize();
}

// Add loop code
void loop()
{
    oCmd.update();
    delay(100);
}
