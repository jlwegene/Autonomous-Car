#ifndef Driver_H
#define Driver_H
#include "Car.h"
#include "mbed.h"
#include "HMC5883L.h"
#include "GPS.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define CLAMP(val,min,max) MAX(MIN(val, max), min)

class Driver{

public:
    Driver(PinName steering, PinName motor, PinName CompassTx, PinName CompassRx, PinName gps_tx, PinName gps_rx);
    
    void turnToHeading(double heading);
    void navigate();

//private:
    Car _car;
    HMC5883L _compass;
    GPS _gps;
    //Ticker _tick;
    bool _updateCompass;
    bool _updateGPS;
    bool _updateLog;
    
};
#endif