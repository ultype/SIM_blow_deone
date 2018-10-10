/*********************************************************************
  PURPOSE: ( Trick numeric )
*********************************************************************/
#include "dynamic.h"

int Dynamic::deriv(Drone *D,Wind *W) {
    D->engine_response(W,this->center,bound_range);   
    if (D->impact==0 && (D->distance >= stable_range) ) {
        D->acc[0] = (D->Eforce[0] - W->Wforce[0])/D->mass ;
        D->acc[1] = (D->Eforce[1] - W->Wforce[1])/D->mass ;
        D->acc[2] = (D->Eforce[2] - W->Wforce[2])/D->mass ;
    } else {
        D->acc[0] = 0.0 ; 
        D->acc[1] = 0.0 ;
        D->acc[2] = 0.0 ;
    }
    return(0);
}

int Dynamic::integ(Drone* D)
{
    int ipass;

    load_state(
        &D->pos[0] ,
        &D->pos[1] ,
        &D->pos[2] ,
        &D->vel[0] ,
        &D->vel[1] ,
        &D->vel[2] ,
        NULL);

    load_deriv(
        &D->vel[0] ,
        &D->vel[1] ,
        &D->vel[2] ,
        &D->acc[0] ,
        &D->acc[1] ,
        &D->acc[2] ,
        NULL);

    ipass = integrate();

    unload_state(
        &D->pos[0] ,
        &D->pos[1] ,
        &D->pos[2] ,
        &D->vel[0] ,
        &D->vel[1] ,
        &D->vel[2] ,
        NULL );

    return(ipass);
}

double Dynamic::impact( Drone* D,Wind *W)
{
    double tgo ; /* time-to-go */
    double now ; /* current integration time. */

    this->rf.error = bound_range - D->distance ;              /* Specify the event boundary. */
    now = get_integ_time() ;               /* Get the current integration time */
    tgo = regula_falsi( now, &(this->rf) ) ;  /* Estimate remaining integration time. */
    if (tgo == 0.0) {                      /* If we are at the event, it's action time! */
        now = get_integ_time() ;
        reset_regula_falsi( now, &(this->rf) ) ;
        D->impact = 1 ;
        D->impactTime = now ;

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

        fprintf(stderr, "\n\nIMPACT: t = %.9f, pos[0] = %.9f\n\n", now, D->pos[0] ) ;
    }
    return (tgo) ;
}

int Dynamic::default_data() {
    this->center[0] = 0.0 ;
    this->center[1] = 0.0 ;
    this->center[2] = 0.0 ;

    this->stable_range  = STABLERANGE ;
    this->bound_range   = BOUNDRANGE ; 
} 

int Dynamic::init(double centerX,double centerY,double centerZ,double bound_range,double stable_range){
    this->center[0] = centerX ;
    this->center[1] = centerY ;
    this->center[2] = centerZ ;
    this->bound_range  = bound_range;
    this->stable_range = stable_range;
}
