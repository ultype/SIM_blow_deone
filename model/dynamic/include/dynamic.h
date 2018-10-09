/*************************************************************************
PURPOSE: ( Dynamic Numeric Model )
**************************************************************************/
#ifndef Dynamic_NUMERIC_H
#define Dynamic_NUMERIC_H

#include "drone.h"
#include "wind.h"

class DYNAMIC{
    int dynamic_integ(DRONE*,WIND*) ;
    int dynamic_deriv(DRONE*,WIND*) ;
    double drone_impact(DRONE*) ;
};

#endif
