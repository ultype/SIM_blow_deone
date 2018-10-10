/************************************************************************
PURPOSE: (Print the final cannon ball state.)
*************************************************************************/
#include "wind.h"
int Wind::shutdown()
{
    this->time = exec_get_sim_time();
    printf( "========================================\n");
    printf( "      Wind State at Shutdown     \n");
    printf( "t = %g\n", this->time);
    printf( "========================================\n");
    return 0 ;
}

int Wind::default_data()
{
    this->Wforce[0] = 0 ;
    this->Wforce[1] = 0 ;
    this->Wforce[2] = 0 ;

    this->magnitude = 0 ;
    this->time = 0 ;

    return 0 ;
}

int Wind::init(double forceX0, double forceY0, double forceZ0) {
    this->Wforce[0] = forceX0 ;
    this->Wforce[1] = forceY0 ;
    this->Wforce[2] = forceZ0 ;

    this->magnitude = 0 ;
    this->time = 0 ;

    return 0 ;
}

double Wind::get_magnitude() {
    double d = 0.0 ;
    d += this->Wforce[0] * this->Wforce[0];
    d += this->Wforce[1] * this->Wforce[1];
    d += this->Wforce[2] * this->Wforce[2];
    this->magnitude = d;
    return d;
}

