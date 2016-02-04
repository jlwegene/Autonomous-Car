#include "Car.h"

Car::Car(PinName stepper, PinName motor) : steer(stepper), drive(motor)
{
    steer.period_ms(20);
    drive.period_ms(20);
}

int clamp(int value, int max, int min){
    return ((value > max) ? max : ((value < min) ? min : value));    
}

void Car::setAngle(int heading){
    steer.pulsewidth_us(1500 + -10 * clamp(heading, 50, -50));
}


void Car::setTorque(int torque){
    drive.pulsewidth_us(1500 + -10 * clamp(torque, 50, -50));
}