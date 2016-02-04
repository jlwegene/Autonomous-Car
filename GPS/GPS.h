#ifndef _MBED_GPS_H_
#define _MBED_GPS_H_
#include "mbedGPSDefs.h"
#include "mbed.h"



    
    
class GPS : RawSerial{
    public:
    GPS(PinName TxPin,PinName RxPin);
    
    void SetBaud(int rate);
    
    ECEFPoint ReadPositionECEF(void);
    
    ECEFDistance DistanceBetweenTwoWP(ECEFPoint p1,ECEFPoint p2);
    
    geodPoint   ReadDecGeodLoc(void);
    geodPoint   ReadRawGeodLoc(void);
    
    bool        FixIs3d(void);
    bool        FixIs2d(void);
    bool        GPSFixValid(void);
    
    GPSInfo info;   //current gps information
       
    private:
    void RxIrqHandler(void);    
    message RxMessageBuffer;
    char insertIndex;
};

#endif