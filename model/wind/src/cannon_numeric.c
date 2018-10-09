/*********************************************************************
  PURPOSE: ( Trick numeric )
*********************************************************************/
#include <stddef.h>
#include <stdio.h>
#include "trick/integrator_c_intf.h"
#include "../include/cannon_numeric.h"

int cannon_deriv(DRONE* C) {

    if (!C->impact) {
        C->acc[0] = 0.0 ;
        C->acc[1] = -9.81 ;
    } else {
        C->acc[0] = 0.0 ;
        C->acc[1] = 0.0 ;
    }
    return(0);
}
int cannon_integ(DRONE* C) {
    int ipass;

    load_state(
        &C->pos[0] ,
        &C->pos[1] ,
        &C->vel[0] ,
        &C->vel[1] ,
        NULL);

    load_deriv(
        &C->vel[0] ,
        &C->vel[1] ,
        &C->acc[0] ,
        &C->acc[1] ,
        NULL);

    ipass = integrate();

    unload_state(
        &C->pos[0] ,
        &C->pos[1] ,
        &C->vel[0] ,
        &C->vel[1] ,
        NULL );

    return(ipass);
}

double cannon_impact( DRONE* C ) {
    double tgo ; /* time-to-go */
    double now ; /* current integration time. */
    
    C->rf.error = C->pos[1] ;              /* Specify the event boundary. */
    now = get_integ_time() ;               /* Get the current integration time */
    tgo = regula_falsi( now, &(C->rf) ) ;  /* Estimate remaining integration time. */ 
    printf("tgo=%4.lf error=%4.lf \n",tgo,(C->rf).error);
    if (tgo == 0.0) {                      /* If we are at the event, it's action time! */
        now = get_integ_time() ;
        reset_regula_falsi( now, &(C->rf) ) ; 
        C->impact = 1 ;
        C->impactTime = now ;
        C->vel[0] = 0.0 ; C->vel[1] = 0.0 ;
        C->acc[0] = 0.0 ; C->acc[1] = 0.0 ;
        fprintf(stderr, "\n\nIMPACT: t = %.9f, pos[0] = %.9f\n\n", now, C->pos[0] ) ;
    }
    return (tgo) ;
}