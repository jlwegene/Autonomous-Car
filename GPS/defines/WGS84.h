/*   
     a   the equatorial earth radius
     f   the "flattening" parameter ( = (a-b)/a ,the ratio of the
         difference between the equatorial and polar radii to a;
         this is a measure of how "elliptical" a polar cross-section
         is).

        The eccentricity e of the figure of the earth is found from
    
        e^2 = 2f - f^2 ,  or  e = sqrt(2f-f^2) .
*/
//For WGS84, 

#define A   6378137.0
#define RF  298.257224
#define F   1/RF
#define E   sqrt(2*f-f^2)

 /*
         a   = 6378137 meters
       (1/f) = 298.257224

(the reciprocal of f is usually given instead of f itself, because the
reciprocal is so close to an integer)

Given latitude (geodetic latitude, not geocentric latitude!), compute

                                  1
        C =  ---------------------------------------------------
             sqrt( cos^2(latitude) + (1-f)^2 * sin^2(latitude) )

and
        S = (1-f)^2 * C .
*/