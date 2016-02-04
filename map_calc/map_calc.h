#ifndef MAP_CALC_H
#define MAP_CALC_H

// conversion based on WGS-84
/** 
*    Calculates the distance between a degree of longitude
*    at a given longitude and latitude.
*   
*    Coversion factor degrees to meters for longitude at a point
*    on the surface of the earth.
*/
double getLon2meters(double lon, double lat, double height);
/** 
*   Calculates the distance between a degree of latitude
*   at a given longitude and latitude.
*
*   Coversion factor degrees to meters for longitude at a point
*   on the surface of the earth.
*/
double getLat2meters(double lon, double lat, double height);

/**
*   Calculate distance between two lonXlat points.
*/
double distance(double lon2met, double lat2met, double lon1, double lat1, double lon2, double lat2);

/**
*   Calculate calculate the heading from lonXlat point 1 and lonXlat point2
*/
double heading(double lon2met, double lat2met, double lon1, double lat1, double lon2, double lat2);
#endif