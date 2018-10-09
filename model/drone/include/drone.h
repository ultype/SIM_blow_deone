/*************************************************************************
PURPOSE: (Represent the state and initial conditions of a cannonball)
**************************************************************************/
#ifndef DRONE_H
#define DRONE_H
#include "trick/regula_falsi.h" //for impacttion dynamic event
#include "WIND.h"

class Drone{

    public:
        double acc[2] ;     /* m/s2 xy-acceleration  */
        double vel[2] ;     /* m/s xy-velocity */
        double pos[2] ;     /* m xy-position */
        double EForce[2];   /* kg.m/s^2 engine force */

        double time;        /* s Model time */

        int impact ;        /* -- Has impact occured? */
        double impactTime;  /* s Time of Impact */
    
        REGULA_FALSI rf ;   //for impacttion dynamic event
        
        int default_data(DRONE*) ;
        int init(DRONE*) ;
        int shutdown(DRONE*) ;
        double engine_respond(WIND) ;
        double center_distance() ;
};

#endif
