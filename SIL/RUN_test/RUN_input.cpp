/*
 To use this as an input file include this file on the command line.
 S_main_${TRICK_HOST_CPU}.exe RUN_<dir>/input.cpp
 Trick will compile and link this file at simulation runtime.  The
 run_me function will automatically be executed during the
 input_processor phase of initialization.
*/

// need access to private/protected things? uncomment these.
//#define private public
//#define protected public

#include "../S_source.hh"
#include "trick/CheckPointRestart_c_intf.hh"
#include "trick/realtimesync_proto.h"
#include "trick/external_application_c_intf.h"

extern "C" int run_event_1() {
    message_publish(1, "event 1 fired!\n") ;
        // modify variables within sim_objects.
    dyn.wind.Wforce[0] = 20.0 ; //this obj located at S_source.hh
    dyn.wind.Wforce[1] = 20.0 ;
    return 0 ;
}

extern "C" int run_event_2() {
    message_publish(1, "event 2 fired!\n") ;
    // modify variables within sim_objects.
    dyn.wind.Wforce[0] = 200.0 ; //this obj located at S_source.hh
    dyn.wind.Wforce[1] = 200.0 ;
    return 0 ;
}

extern "C" int run_event_3() {
    message_publish(1, "event 3 fired!\n") ;
    printf("time=%4lf\nWforce[%4lf %4lf %4lf]\nEforce[%4lf %4lf %4lf]\nAcc[%4lf %4lf %4lf]\nvel[%4lf %4lf %4lf]\npos[%4lf %4lf %4lf]\n",
            dyn.drone.time,
            dyn.wind.Wforce[0], dyn.wind.Wforce[1], dyn.wind.Wforce[2],
            dyn.drone.Eforce[0], dyn.drone.Eforce[1], dyn.drone.Eforce[2],
            dyn.drone.acc[0],    dyn.drone.acc[1],    dyn.drone.acc[2],
            dyn.drone.vel[0],    dyn.drone.vel[1],    dyn.drone.vel[2],
            dyn.drone.pos[0],    dyn.drone.pos[1],    dyn.drone.pos[2]    );
    return 0 ;
}

extern "C" int run_event_4() {
    message_publish(1, "event 4 fired!\n") ;
    return 0 ;
}

extern "C" int run_event_before() {
    printf("time=%4lf\nWforce[%4lf %4lf %4lf]\nEforce[%4lf %4lf %4lf]\nAcc[%4lf %4lf %4lf]\nvel[%4lf %4lf %4lf]\npos[%4lf %4lf %4lf]\n",
            dyn.drone.time,
            dyn.wind.Wforce[0], dyn.wind.Wforce[1], dyn.wind.Wforce[2],
            dyn.drone.Eforce[0], dyn.drone.Eforce[1], dyn.drone.Eforce[2],
            dyn.drone.acc[0],    dyn.drone.acc[1],    dyn.drone.acc[2],
            dyn.drone.vel[0],    dyn.drone.vel[1],    dyn.drone.vel[2],
            dyn.drone.pos[0],    dyn.drone.pos[1],    dyn.drone.pos[2]    );
    return 0 ;
}

extern "C" int run_event_before2() {
    message_publish(1, "event before2 fired!\n") ;
    return 0 ;
}

extern "C" int run_event_after() {
    message_publish(1, "event after fired!\n") ;
    return 0 ;
}

extern "C" int remove_events() {
    event_manager_remove_event(event_manager_get_event("event_3")) ;
    event_manager_remove_event(event_manager_get_event("event_before")) ;
    event_manager_remove_event(event_manager_get_event("event_after")) ;
    return 0 ;
}

extern "C" int run_me() {

    // modify variables within sim_objects.
    dyn.wind.Wforce[0] = 20.0 ; //this obj located at S_source.hh
    dyn.wind.Wforce[1] = 20.0 ;

    checkpoint_pre_init(true) ;

    // add read events
    jit_add_read( 20.0 , "run_event_1" ) ; //在90s 啟動  run_event_1
    jit_add_read( 80.0 , "run_event_2" ) ; //在80s 啟動  run_event_2

    // add cyclic event
    jit_add_event( "run_event_3" , "Acc Check" , 10.0 ) ; //每間隔 100.0s 啟動 一次  run_event_3 (cyclic,perriod=100.0)

    // events tied to jobs
//    jit_add_event_before( "run_event_before", "event_before", "dyn.dynamic.deriv" ) ;
//    jit_add_event_after( "run_event_after", "event_after", "ball.obj.state_print" ) ;

    // add a read event that removes all other events.
    jit_add_read( 100.0 , "remove_events" ) ;

//    jit_add_read( 190.0 , "hidden_event" ) ;

    exec_set_terminate_time(101.0) ;

/*
    real_time_enable() ;
    trick_real_time.itimer.enable() ;
    sim_control_panel_set_enabled(true) ;
*/

    return 0 ;
}
