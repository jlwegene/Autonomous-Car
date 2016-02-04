#include "Driver.h"
#include "map_calc.h"

static const double RATE = 0.05;
static const double Kp   = 0.7;
static const double Ki   = 0.00;
static const double Kd   = 0.0;
// End op path near owen hall
//static const double goalLat = 39.166749;
//static const double goalLon = -86.523825;
//static const double goalAlt = 217.0;
static const double goalLat = 39.165971;
static const double goalLon = -86.523787;
static const double goalAlt = 217.0;

Serial logger(USBTX, USBRX);

Driver::Driver(PinName steering, PinName motor, PinName CompassTx, PinName CompassRx, PinName gps_tx, PinName gps_rx):
     _car(steering, motor), _compass(CompassTx, CompassRx), _gps(gps_tx, gps_rx)
{
    logger.baud(115200);    
};

void Driver::turnToHeading(double desired){
    
    static double integral = 0;
    static double previous_error = 0;
    
    
    //double actual = _compass.getHeadingXYDeg();
    double actual = _gps.info.MagneticTrack;
    
    double error = desired - actual;
    
    if (error > 180) error -= 360;
    else if (error < -180) error += 360;
    
    integral += error * RATE;
    double derivative = (error - previous_error)/RATE;
    double output     = Kp*error + Ki*integral + Kd*derivative;
    previous_error = error; 
    
    long correction_angle = (long) output;
    _car.setAngle(correction_angle);
    
    if(_updateLog){
        logger.printf("-----End of PID Controller----------------------------------------\n\r");
        logger.printf("desired heading %f \r\n", desired);
        logger.printf("actual heading %f \r\n", actual);
        logger.printf("output %f\n\r", output);
        logger.printf("correction angle %ld\n\r", correction_angle);
              
    }
}



void Driver::navigate(){
    static geodPoint curLocation;
    // get a gps fix
    while(!_gps.FixIs3d()); // spin until a gps fix is acquired
    curLocation = _gps.ReadDecGeodLoc();
    // get conversion factors for this location
    static double lon2m = getLon2meters(curLocation.longitude, curLocation.latitude, curLocation.altitude);
    static double lat2m = getLat2meters(curLocation.longitude, curLocation.latitude, curLocation.altitude);
    // find an initial heading to waypoint
    static double goalHeading = heading(lon2m, lat2m, curLocation.longitude, curLocation.latitude, goalLon, goalLat);
    static double goalDistance = distance(lon2m, lat2m, curLocation.longitude, curLocation.latitude, goalLon, goalLat);
    
    _car.setTorque(14);
    
    while(goalDistance > 20.00){
        // System tick has set the gps flag
        if(_updateGPS){
            _updateGPS = ! _updateGPS;
            if(_gps.GPSFixValid()){
                curLocation = _gps.ReadDecGeodLoc();
                goalHeading  = heading(lon2m, lat2m, curLocation.longitude, curLocation.latitude, goalLon, goalLat);
                goalDistance = distance(lon2m, lat2m, curLocation.longitude, curLocation.latitude, goalLon, goalLat);
            }
        }
        // Systrm  tick has set the compass flag
        if(_updateCompass){
            _updateCompass = !_updateCompass;
            turnToHeading((long)goalHeading);   
        }
        if(_updateLog){
            _updateLog = ! _updateLog;
            logger.printf("-----End of navigate loop----------------------------------------\n\r");
            logger.printf("Goal lat %f lon %f\r\n", goalLat, goalLon);
            logger.printf("Current lat %f lon %f\r\n", curLocation.latitude, curLocation.longitude);
            logger.printf("Goal heading %f distance %f\n\r", goalHeading, goalDistance);
            logger.printf("Compass heading %f\n\r", _compass.getHeadingXYDeg());
              
        }
    }
    while(1) _car.setTorque(0);
}
