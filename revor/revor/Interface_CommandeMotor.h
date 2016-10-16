//
//  Interface_CommandeMotor.h
//  revor
//

#ifndef Interface_CommandeMotor_h
#define Interface_CommandeMotor_h

#include "DC_Motor.hpp"
#include "Wii_Chuck.h"
#include <string.h>

class Interface_CommandeMotor
{
    
public:
    
    // Constructor
    Interface_CommandeMotor();
    
    // Destructor
    ~Interface_CommandeMotor();
    
    // Getteur Setteur
    float getSpeed() const;
    void setSpeed(const float);
    
    // Control function
    void updateSpeed();
    void decode_Direction();
    

    
private:
    
    // Motor Rover
    DC_Motor* mpMotor;
    Wii_Chuck* mpChuck;
    
    float mSpeed;
    
    
};


#endif /* Interface_CommandeMotor_h */
