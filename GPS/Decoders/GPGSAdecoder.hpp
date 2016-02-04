#ifndef _GPGSAdecoder_H_
#define _GPGSAdecoder_H_
#include "mbed.h"
#include "mbedGPSDefs.h"



void DecodeGPGSA(char * tokenStr,GPSInfo& data)
{
    int parameterCount = 0;
    char *rest; // to point to the rest of the string after token extraction.
    char *token; // to point to the actual token returned.
    char *ptr = tokenStr; // make q point to start of hello.
    token = strtok_r(ptr, ",",&rest);
    while (token != NULL)
    {
        //printf("DEBUG ... PARAM_CNT:%d\n",parameterCount);
        if(parameterCount == 1)
            data.mode = *token;
            
        if(parameterCount == 2){
            data.fix = atoi(token);
        }
            
        if(parameterCount == (3 + data.TrackedSatCnt)){
            data.PDOP = atof(token);
            //printf("DEBUG ... PDOP:%f\n",data.PDOP);
        }   
        if(parameterCount == (3 + data.TrackedSatCnt + 1)){
            data.HDOP = atof(token);
            //printf("DEBUG ... HDOP:%f\n",data.HDOP);
        }
        if(parameterCount == (3 + data.TrackedSatCnt + 2)){
            data.VDOP = atof(token);
            //printf("DEBUG ... VDOP:%f\n",data.VDOP);
        }
        parameterCount++;
        ptr = rest; // rest contains the left over part..assign it to ptr.
        token = strtok_r(ptr, ",",&rest);
    }
}
#endif