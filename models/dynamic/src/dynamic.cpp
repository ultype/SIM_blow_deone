/*********************************************************************
  PURPOSE: ( Trick numeric )
*********************************************************************/
#include "dynamic.hh"

Dynamic::Dynamic() {
    this->default_data();
}

int Dynamic::deriv(Drone *D,Wind *W) {
    D->engine_response(W,this->center,this->bound_range);   
    D->acc[0] = (D->Eforce[0] + W->Wforce[0])/D->mass ;
    D->acc[1] = (D->Eforce[1] + W->Wforce[1])/D->mass ;
    D->acc[2] = (D->Eforce[2] + W->Wforce[2])/D->mass ;
    return 0;
}

int Dynamic::integ(Drone* D,double step) {
    double tempVX=D->vel[0] ;
    double tempVY=D->vel[1] ;
    double tempVZ=D->vel[2] ;
    D->vel[0] = D->vel[0] + D->acc[0] * step;
    D->vel[1] = D->vel[1] + D->acc[1] * step;
    D->vel[2] = D->vel[2] + D->acc[2] * step;
    D->pos[0] = D->pos[0] +step * (D->vel[0]+tempVX)/2.0; //trapzoidal
    D->pos[1] = D->pos[1] +step * (D->vel[1]+tempVY)/2.0; //trapzoidal
    D->pos[2] = D->pos[2] +step * (D->vel[2]+tempVZ)/2.0; //trapzoidal
    return 0;
}

double Dynamic::impact( Drone* D,Wind *W)
{
    double tgo = 1.0; /* time-to-go */
//    double now ; /* current integration time. */

    if (tgo == 0.0) {                      /* If we are at the event, it's action time! */
        D->impact = 1 ;
//        D->impactTime = now ;

        D->vel[0] = 0.0 ;
        D->vel[1] = 0.0 ;
        D->vel[2] = 0.0 ;

        D->acc[0] = 0.0 ;
        D->acc[1] = 0.0 ;
        D->acc[2] = 0.0 ;

        D->Eforce[0] = 0.0 ;
        D->Eforce[1] = 0.0 ;
        D->Eforce[2] = 0.0 ;
        
        W->Wforce[0] = 0.0 ;
        W->Wforce[1] = 0.0 ;
        W->Wforce[2] = 0.0 ;

        fprintf(stderr, "\n\nIMPACT: t =, pos[0] = %.9f\n\n", D->pos[0] ) ;
    }
    return (tgo) ;
}

int Dynamic::default_data() {
    this->center[0] = 0.0 ;
    this->center[1] = 0.0 ;
    this->center[2] = 0.0 ;

    this->stable_range  = STABLERANGE ;
    this->bound_range   = BOUNDRANGE ; 
    return 0;
} 

int Dynamic::init(double centerX,double centerY,double centerZ,double bound_range,double stable_range){
    this->center[0] = centerX ;
    this->center[1] = centerY ;
    this->center[2] = centerZ ;
    this->bound_range  = bound_range;
    this->stable_range = stable_range;
    return 0;
}
