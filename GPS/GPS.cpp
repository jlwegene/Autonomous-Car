#include "GPS.h"
#include "GPSUtils.hpp"

GPS::GPS(PinName tx, PinName rx) : RawSerial(tx, rx)
{
    RawSerial::baud(57600);
    attach(this, &GPS::RxIrqHandler);
}

void GPS::SetBaud(int rate){
    RawSerial::baud(rate);
    }

void GPS::RxIrqHandler(void)
{
    char in;
    while(RawSerial::readable())
    {
        in = RawSerial::getc();
        if(in == START_CHAR)
        {
            insertIndex = 0;
            RxMessageBuffer.data[(insertIndex++)%RX_BUFFER_SIZE] = in;
        }
        else if(in == END_CHAR)
        {
            RxMessageBuffer.data[(insertIndex++)%RX_BUFFER_SIZE] = 0;
            DecodeMessage(RxMessageBuffer,info);
        }
        else
            RxMessageBuffer.data[(insertIndex++)%RX_BUFFER_SIZE] = in;
    }
}


ECEFPoint GPS::ReadPositionECEF(void)
{   
    return GeoDesicToECEF(ReadDecGeodLoc());
}
ECEFDistance GPS::DistanceBetweenTwoWP(ECEFPoint p1,ECEFPoint p2)
{
    return DistanceBetweenTwoECEFPoints(p1,p2);
}

geodPoint   GPS::ReadDecGeodLoc(void){
    geodPoint newLoc;
    newLoc.latitude = nmea_to_dec(info.latitude,info.latLoc);
    newLoc.longitude = nmea_to_dec(info.longitude,info.lonLoc);
    newLoc.altitude = info.GPSAltitude;
    return newLoc;
    }
    
geodPoint   GPS::ReadRawGeodLoc(void){
    geodPoint newLoc;
    newLoc.latitude = info.latitude;
    newLoc.longitude = info.longitude;
    newLoc.altitude = info.GPSAltitude;
    return newLoc;
    }
    
    
bool    GPS::FixIs3d(void){
    return (info.fix == 3);
    }
bool    GPS::FixIs2d(void){
    return (FixIs3d() || (info.fix == 2));
    }
bool    GPS::GPSFixValid(void){
        return (info.GPSStatus == 'A');
    }


