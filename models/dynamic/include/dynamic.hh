/********************************* TRICK HEADER *******************************
PURPOSE:
      (dynamic module)
LIBRARY DEPENDENCY:
      ((../src/dynamic.cpp))
PROGRAMMERS:
      (((ultype) () () () ))
*******************************************************************************/
#ifndef Dynamic_HH
#define Dynamic__HH
#include <stddef.h>
#include <stdio.h>
#include "trick/integrator_c_intf.h"
#include "trick/regula_falsi.h" //for impact dynamic event
#include "wind.hh"
#include "drone.hh"
#define STABLERANGE 0.001;
#define BOUNDRANGE 5000;

class Dynamic {
public:

    double center[3] ;
    double stable_range ; 
    double bound_range ;
    double time ; 
    Dynamic();
    ~Dynamic(){};
    int integ(Drone*,double) ;
    int deriv(Drone*,Wind*) ;
    double impact(Drone*,Wind*) ;

    int default_data() ;
    int init(double centerX, double centerY, double centerZ, 
             double bound_range, double stable_range) ;
};

#endif
