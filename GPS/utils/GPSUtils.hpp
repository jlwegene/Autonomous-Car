#ifndef _GPSUTILS_H_
#define _GPSUTILS_H_

#include "mbedGPSDefs.h"
#include "GPGGAdecoder.hpp"
#include "GPVTGdecoder.hpp"
#include "GPGSAdecoder.hpp"
#include "GPRMCdecoder.hpp"
#include "WGS84.h"

#define PI  3.141592653589793238462643383279502884
#define RADIANS_TO_DEGREES(radians) ((radians) * (180.0 / PI))
#define DEGREES_TO_RADIANS   ( PI / 180.0)
#define WGS84_A     6378137.000
//298.257223563
#define WGS84_E     0.081819190842621


/*
    Source of information about nema sentences :
    http://www.gpsinformation.org/dale/nmea.htm
*/
void DecodeMessage(message& msg,GPSInfo& data)
{
    
    if(strstr(msg.data,GPS_CMD_GPGGA)){
        DecodeGPGGA(msg.data,data);
        }
        
    if(strstr(msg.data,GPS_CMD_GPVTG)){
        DecodeGPVTG(msg.data,data);
        }
        
    if(strstr(msg.data,GPS_CMD_GPGSA)){
        DecodeGPGSA(msg.data,data);
        }
    if(strstr(msg.data,GPS_CMD_GPRMC)){
        DecodeGPRMC(msg.data,data);
        }
}

ECEFPoint GeoDesicToECEF(geodPoint p)
{
    ECEFPoint newECEFpoint;
    double lat = 0.0;
    double lon = 0.0;
    lat = p.latitude;
    lon = p.longitude;

    double clat = cos(lat * DEGREES_TO_RADIANS);
    double slat = sin(lat * DEGREES_TO_RADIANS);
    double clon = cos(lon * DEGREES_TO_RADIANS);
    double slon = sin(lon * DEGREES_TO_RADIANS);
    
    double N = WGS84_A / sqrt(1.0 - WGS84_E * WGS84_E * slat * slat);

    newECEFpoint.x = (N + p.altitude) * clat * clon;
    newECEFpoint.y = (N + p.altitude) * clat * slon;
    newECEFpoint.z = (N * (1.0 - WGS84_E * WGS84_E) + p.altitude) * slat;
    
    return newECEFpoint;
}

ECEFDistance DistanceBetweenTwoECEFPoints(ECEFPoint p1, ECEFPoint p2)
{
    ECEFDistance newDistance;
    newDistance.dx = p1.x-p2.x;
    newDistance.dy = p1.y-p2.y;
    newDistance.dz = p1.z-p2.z;
    newDistance.d = sqrt((newDistance.dx*newDistance.dx) + (newDistance.dy*newDistance.dy) + (newDistance.dz*newDistance.dz));
    return newDistance;
}

float nmea_to_dec(double nema_coor, char nsew) {
    int degree = (int)(nema_coor/100);
    double minutes = nema_coor - degree*100;
    double dec_deg = minutes / 60;
    double decimal = degree + dec_deg;
    if (nsew == 'S' || nsew == 'W') { // return negative
        decimal *= -1;
    }
    return decimal;
}
#endif