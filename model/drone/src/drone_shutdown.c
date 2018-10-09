/************************************************************************
PURPOSE: (Print the final drone ball state.)
*************************************************************************/
#include <stdio.h>
#include "../include/drone.h"
#include "trick/exec_proto.h"

int drone_shutdown( DRONE* C) {
    printf( "enter shutdown\n");
    double t = exec_get_sim_time();
    printf( "========================================\n");
    printf( "      drone State at Shutdown     \n");
    printf( "t = %g\n", t);
    printf( "pos = [%.9f, %.9f]\n", C->pos[0], C->pos[1]);
    printf( "vel = [%.9f, %.9f]\n", C->vel[0], C->vel[1]);
    printf( "========================================\n");
    return 0 ;
}