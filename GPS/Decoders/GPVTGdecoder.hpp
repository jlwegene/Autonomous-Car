#ifndef _GPVTGdecoder_H_
#define _GPVTGdecoder_H_

#include "mbed.h"
#include "mbedGPSDefs.h"

void DecodeGPVTG(char * tokenStr,GPSInfo& data)
{
    int parameterCount = 0;
    char *rest; // to point to the rest of the string after token extraction.
    char *token; // to point to the actual token returned.
    char *ptr = tokenStr; // make q point to start of hello.
    token = strtok_r(ptr, ",",&rest);
    while (token != NULL)
    {
        if(parameterCount == 1)
            data.TrueTrack = atof(token);
            
        if(parameterCount == 3)
            data.MagneticTrack = atof(token);
            
        if(parameterCount == 5)
            data.GroundSpeedN = atof(token);
            
        if(parameterCount == 7)
            data.GroundSpeedK = atof(token);
            
        parameterCount++;
        ptr = rest; // rest contains the left over part..assign it to ptr.
        token = strtok_r(ptr, ",",&rest);
    }
}
#endif