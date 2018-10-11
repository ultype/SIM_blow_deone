/******************************* TRICK HEADER ****************************
PURPOSE: (Set the initial data values)
*************************************************************************/
/* Model Include files */

#include "drone.hh"
Drone::Drone() {
    this->default_data();
}

/* default data job */
int Drone::default_data() {
    this->acc[0] = 0 ;
    this->acc[1] = 0 ;
    this->acc[2] = 0 ;

    this->vel[0] = 0 ;
    this->vel[1] = 0 ;
    this->vel[2] = 0 ;

    this->pos[0] = 0 ;
    this->pos[1] = 0 ;
    this->pos[2] = 0 ;

    this->Eforce[0] = 0 ;
    this->Eforce[1] = 0 ;
    this->Eforce[2] = 0 ;

    this->time = 0 ;
    this->distance = 0 ;
    this->mass = DRONE_MASS;

    this->impact = 0 ;
    this->impactTime = 0 ;

    return 0 ;
}

/* initialization job */
int Drone::init(double posX0, double posY0, double posZ0,double* center) {

    this->acc[0] = 0 ;
    this->acc[1] = 0 ;
    this->acc[2] = 0 ;

    this->vel[0] = 0 ;
    this->vel[1] = 0 ;
    this->vel[2] = 0 ;

    this->pos[0] = posX0 ;
    this->pos[1] = posY0 ;
    this->pos[2] = posZ0 ;

    this->Eforce[0] = 0 ;
    this->Eforce[1] = 0 ;
    this->Eforce[2] = 0 ;

    this->time = 0 ;
    this->distance = this->get_distance(center);
    this->mass = DRONE_MASS;

    this->impact = 0 ;
    this->impactTime = 0 ;
    return 0 ;
}

double Drone::get_distance(double* center) {
    double d = 0.0 ;
    double temp;
    temp = center[0] - this->pos[0];
    d += temp * temp ;
    temp = center[1] - this->pos[1];
    d += temp * temp ;
    temp = center[2] - this->pos[2];
    d += temp * temp ;
    this->distance = d;
    return d;
}

int Drone::engine_response(Wind* w, double *center, double bound_range) {

    if (!this->almost_equal(this->get_distance(center), 0.0, bound_range)) {

        int pos_to_centerX, pos_to_centerY, pos_to_centerZ;
        int forceX,forceY,forceZ;

        pos_to_centerX= center[0] - this->pos[0];
        pos_to_centerY= center[1] - this->pos[1];
        pos_to_centerZ= center[2] - this->pos[2];

        if ( !this->almost_equal(pos_to_centerX, 0.0, AXIS_TOLERANCE) ) {
            forceX = pos_to_centerX * SPRINGK - this->vel[0] * SPRINGC;
            if (fabs(forceX) > MAX_AXIS_EFORCE) {
                this->Eforce[0] = MAX_AXIS_EFORCE ;
            } else {
                this->Eforce[0] = forceX;
            }
        }

        if ( !this->almost_equal(pos_to_centerY, 0.0, AXIS_TOLERANCE) ) {
            forceY = pos_to_centerY * SPRINGK - this->vel[1] * SPRINGC;
            if (fabs(forceY) > MAX_AXIS_EFORCE) {
                this->Eforce[1] = MAX_AXIS_EFORCE ;
            } else {
                this->Eforce[1] = forceY;
            }
        }

        if ( !this->almost_equal(pos_to_centerZ, 0.0, AXIS_TOLERANCE) ) {
            forceZ = pos_to_centerZ * SPRINGK - this->vel[2] * SPRINGC;
            if (fabs(forceZ) > MAX_AXIS_EFORCE) {
                this->Eforce[2] = MAX_AXIS_EFORCE ;
            } else {
                this->Eforce[2] = forceZ;
            }
        }

    }

    return 0;
}

int Drone::shutdown()
{
    double t = exec_get_sim_time();
    printf( "========================================\n");
    printf( "      drone State at Shutdown     \n");
    printf( "t = %g\n", t);
    //printf( "pos = [%.9f, %.9f]\n", C->pos[0], C->pos[1]);
    //printf( "vel = [%.9f, %.9f]\n", C->vel[0], C->vel[1]);
    printf( "========================================\n");
    return 0 ;
}

bool almost_equal(double a, double b, double tolerance)
{
    if(fabs(a-b) <= tolerance) {
        return true;
    }
    return false;
}





