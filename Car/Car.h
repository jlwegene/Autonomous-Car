#ifndef Car_H
#define Car_H

#include "mbed.h"
class Car{

public:
    Car(PinName stepper, PinName motor);
    
    //-50 to 50
    void setAngle(int heading);
    
    //-50 to 50
    void setTorque(int torque);

private:
    PwmOut steer;
    PwmOut drive;
};
#endif