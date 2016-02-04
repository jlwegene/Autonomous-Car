#ifndef _GPRMCdecoder_H_
#define _GPRMCdecoder_H_

#include "mbed.h"
#include "mbedGPSDefs.h"

void DecodeGPRMC(char * tokenStr,GPSInfo& data){
    int parameterCount = 0;
    char *rest; // to point to the rest of the string after token extraction.
    char *token; // to point to the actual token returned.
    char *ptr = tokenStr; // make q point to start of hello.
    token = strtok_r(ptr, ",",&rest);
    while (token != NULL){
        
        if(parameterCount == 1){    //utc fix time
            data.time.time[0] = *token;
            data.time.time[1] = *(token+1);
            data.time.time[2] = *(token+2);
            data.time.time[3] = *(token+3);
            data.time.time[4] = *(token+4);
            data.time.time[5] = *(token+5);
            data.time.time[6] = '\0'; //properly finish the string
            data.time.hour = (data.time.time[0]-0x30)*10 + (data.time.time[1]-0x30);
            data.time.min = (data.time.time[2]-0x30)*10 + (data.time.time[3]-0x30);
            data.time.sec = (data.time.time[4]-0x30)*10 + (data.time.time[5]-0x30);
            if(*(token+6) == '.')//check is sentence has ms precision, if so parse it
                data.time.msec =  (*(token+7)-0x30)*100 +(*(token+8)-0x30)*10 + (*(token+9)-0x30);
            else
                data.time.msec = 0;
            
            }
        if(parameterCount == 2){    //GPS fix status
            data.GPSStatus = *token;
            }
        if(parameterCount == 9){    //fix date
            data.date.date[0] = *token;
            data.date.date[1] = *(token+1);
            data.date.date[2] = *(token+2);
            data.date.date[3] = *(token+3);
            data.date.date[4] = *(token+4);
            data.date.date[5] = *(token+5);
            data.date.date[6] = '\0'; //properly finish the string
            data.date.day = (data.date.date[0]-0x30)*10 + (data.date.date[1]-0x30);
            data.date.month = (data.date.date[2]-0x30)*10 + (data.date.date[3]-0x30);;
            data.date.year = (data.date.date[4]-0x30)*10 + (data.date.date[5]-0x30);;
            }    
  
        parameterCount++;
        ptr = rest; // rest contains the left over part..assign it to ptr.
        token = strtok_r(ptr, ",",&rest);
    }
}
#endif