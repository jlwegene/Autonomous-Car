#include "mbed.h"


static const double PI = 3.141592653589793238462643383279502884;
static const double DEGREE_2_RADIAN = (PI / 180.0);

// Radiuses of the eliptical earth in meters
static const double EQUITORIAL_RADIUS  = 6378137.0;
static const double EQUITORIAL_RADIUS2 = EQUITORIAL_RADIUS * EQUITORIAL_RADIUS;
static const double POLAR_RADIUS  = 6356752.3;
static const double POLAR_RADIUS2 = POLAR_RADIUS * POLAR_RADIUS;

/** 
*    Calculates the distance between a degree of longitude
*    at a given longitude and latitude.
*   
*    Coversion factor degrees to meters for longitude at a point
*    on the surface of the earth.
*/
double getLon2meters(double lon, double lat, double height){
  double cos_lat  = cos(lat*DEGREE_2_RADIAN);
  double cos_lat2 = cos_lat * cos_lat;
  double sin_lat  = sin(lat*DEGREE_2_RADIAN);
  double sin_lat2 = sin_lat * sin_lat;
  double denom2   = (EQUITORIAL_RADIUS2 * cos_lat2) + 
                    (POLAR_RADIUS2 * sin_lat2);
  double denominator = sqrt(denom2);
  double numerator   = EQUITORIAL_RADIUS2;
  return DEGREE_2_RADIAN * ((numerator / denominator) + height) * cos_lat;
}

/** 
*   Calculates the distance between a degree of latitude
*   at a given longitude and latitude.
*
*   Coversion factor degrees to meters for longitude at a point
*   on the surface of the earth.
*/

double getLat2meters(double lon, double lat, double height){
  double cos_lat  = cos(lat*DEGREE_2_RADIAN);
  double cos_lat2 = cos_lat * cos_lat;
  double sin_lat  = sin(lat*DEGREE_2_RADIAN);
  double sin_lat2 = sin_lat * sin_lat;
  double denom2   = (EQUITORIAL_RADIUS2 * cos_lat2) + 
                    (POLAR_RADIUS2 * sin_lat2);
  double denominator = pow(denom2, 1.5);
  double numerator   = EQUITORIAL_RADIUS2 * POLAR_RADIUS2;
  return DEGREE_2_RADIAN * ((numerator / denominator) + height);
}

// Calculate distance between two lonXlat points
double distance(double lon2met, double lat2met, double lon1, double lat1, double lon2, double lat2)
{
  double delta_lon = lon1 - lon2;
  double delta_lat = lat1 - lat2;
  double delta_x = lon2met * delta_lon;
  double delta_y = lat2met * delta_lat;
  double delta_x2 = delta_x * delta_x;
  double delta_y2 = delta_y * delta_y;
  return sqrt(delta_x2 + delta_y2);
}

// Calculate calculate the heading from lonXlat point 1 and lonXlat point2
double heading(double lon2met, double lat2met, double lon1, double lat1, double lon2, double lat2){
  // avoid division by zero
  if (lon1 == lon2) return (lat1 < lat2) ? 0 : 180;
  
  // convert to distance in meters x and y
  double delta_x = lat2met * (lat1 - lat2);
  double delta_y = lon2met * (lon1 - lon2);
  
  // angle between the two points
  double rel_heading = atan(delta_x / delta_y)*180/PI;
  
//  // correct for north or south
  return ((lon1 < lon2) ? 90.0 : 270.0) - rel_heading; 

}
