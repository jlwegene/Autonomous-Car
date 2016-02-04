#ifndef _MBED_GPS_DEFS_H_
#define _MBED_GPS_DEFS_H_
//=======================================================================
// GPS Special caracters
#define START_CHAR      '$'
#define END_CHAR        0x0D
//=======================================================================
// GPS BUFFER SIZE
#define RX_BUFFER_SIZE  80
//=======================================================================
// GPS COMMANDS
#define GPS_CMD_GPGGA   "$GPGGA"
#define GPS_CMD_GPGSA   "$GPGSA"
#define GPS_CMD_GPGSV   "$GPGSV"
#define GPS_CMD_GPRMC   "$GPRMC"
#define GPS_CMD_GPVTG   "$GPVTG"

//=======================================================================
// GPS MESSAGE STRUCTURE
typedef struct {
    char data[RX_BUFFER_SIZE];
    }message;
    
//=======================================================================
// GPS COORDINATE POINT STRUCTURES  
typedef struct{
    double  latitude;
    double  longitude;
    float   altitude;
    }geodPoint;  
     
typedef struct{
    double x;
    double y;
    double z;
    }ECEFPoint;
    
typedef struct{
    float dx;
    float dy;
    float dz;
    float d;
    }ECEFDistance;

typedef struct{
    char    time[7];
    char    hour;
    char    min;
    char    sec;
    int     msec;
    }FIXtime;
typedef struct{
    char    date[7];
    char    day;
    char    month;
    char    year;
    }FIXDate;
    
typedef struct{
    double  latitude;
    char    latLoc;
    double  longitude;
    char    lonLoc;
    float   GPStime;
    char    GPSStatus;
    char    FixQal;
    float   GPSAltitude;
    float   GEOIDHeight;
    
    float   TrueTrack;      //Relative to true north
    float   MagneticTrack;  //Relative to magnetic north
    float   GroundSpeedN;
    float   GroundSpeedK;
    
    char    TrackedSatCnt;
    
    char    mode;   //A=automatic M=manual
    char    fix;    //1=not valid, 2=2d, 3=3d

    float   PDOP,HDOP,VDOP;
    
    FIXtime time;
    FIXDate date;
    }GPSInfo;
#endif