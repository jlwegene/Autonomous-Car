#ifndef _GPGGAdecoder_H_
#define _GPGGAdecoder_H_
#include "mbed.h"
#include "mbedGPSDefs.h"

void DecodeGPGGA(char * tokenStr,GPSInfo& data)
{
    int parameterCount = 0;
    char *rest; // to point to the rest of the string after token extraction.
    char *token; // to point to the actual token returned.
    char *ptr = tokenStr; // make q point to start of hello.
    token = strtok_r(ptr, ",",&rest);
    while (token != NULL)
    {
        if(parameterCount == 1)
            data.GPStime = atof(token);
            
        if(parameterCount == 2)
            data.latitude = atof(token);
            
        if(parameterCount == 3)
            data.latLoc = *token;
                      
        if(parameterCount == 4)
            data.longitude = atof(token);
            
        if(parameterCount == 5)
            data.lonLoc = *token;
            
        if(parameterCount == 6)
            data.FixQal = atoi(token);
            
        if(parameterCount == 7)
            data.TrackedSatCnt = atoi(token);
            
        if(parameterCount == 8)
            data.HDOP = atof(token);
            
        if(parameterCount == 9)
            data.GPSAltitude = atof(token);
            
        if(parameterCount == 11)
            data.GEOIDHeight = atof(token);
            
        parameterCount++;
        ptr = rest; // rest contains the left over part..assign it to ptr.
        token = strtok_r(ptr, ",",&rest);
    }
    /*printf("Time:%lf\n",data.GPStime);
    printf("Latitude:%4.4lf\n",data.latitude);
    printf("Longitude:%4.4lf\n",data.longitude);
    printf("GPS FIX:%d\n",data.GPSFix);
    printf("GPS Altitude:%f\n",data.GPSAltitude);
    printf("GPS Geoide Heigth:%f\n",data.GEOIDHeight);*/

}
#endif