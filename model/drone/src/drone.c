/******************************* TRICK HEADER ****************************
PURPOSE: (Set the initial data values)
*************************************************************************/

/* Model Include files */
#include <math.h>
#include "../include/cannon.h"

/* default data job */
int Drone::default_data( DRONE* C ) {
    this->acc[0]=0;
    this->acc[1]=0;

    this->vel[0]=0;
    this->vel[1]=0;

    this->pos[0]=0;
    this->pos[1]=0;    
    return 0 ;
}

/* initialization job */
Drone::init(double posX0, double posY0) {
    this->acc[0]=0;
    this->acc[1]=0;

    this->vel[0]=0;
    this->vel[1]=0;

    this->pos[0]=posX0;
    this->pos[1]=posY0;
    return 0 ; 
}