/********************************* TRICK HEADER *******************************
PURPOSE:
      (Drone module)
LIBRARY DEPENDENCY:
      ((../src/drone.cpp))
PROGRAMMERS:
      (((ultype) () () () ))
*******************************************************************************/
#ifndef DRONE_HH
#define DRONE_HH

#include "wind.hh"
#include "drone.hh"
#include "trick/exec_proto.h"
#include <math.h>

#define DISTANCE_TOLERANCE 0.00001
#define AXIS_TOLERANCE 0.000001

#define MAX_AXIS_EFORCE 100
#define SPRINGK 6  /* like spring k*/
#define SPRINGC 2  /* like spring C*/
#define DRONE_MASS 20


class Drone
{
public:
    // normal var
    double acc[3] ;     /* m/s2 xy-acceleration */
    double vel[3] ;     /* m/s xy-velocity */
    double pos[3] ;     /* m xy-position */
    double Eforce[3];   /* kg.m/s^2 engine force */
    double time;        /* s Model time */
    double distance;    /* m distance from center to drone*/
    double mass;        /* kg drone mass */

    // status variable
    int impact ;        /* -- Has impact occured? */
    double impactTime;  /* s Time of Impact */
    Drone();
    ~Drone(){};
    int default_data() ;
    int init(double posX0, double posY0, double posZ0, double *center) ;
    int shutdown() ;
    int engine_response(Wind* w,double* center,double bound_ranges) ;
    double get_distance(double* center) ;
    bool almost_equal(double a, double b, double tolerance) ; // to avoid sensitive respond
};

#endif
