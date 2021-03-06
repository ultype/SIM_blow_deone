/********************************* TRICK HEADER *******************************
PURPOSE:
      (Wind module)
LIBRARY DEPENDENCY:
      ((../src/wind.cpp))
PROGRAMMERS:
      (((ultype) () () () ))
*******************************************************************************/
#ifndef WIND_HH
#define WIND_HH
#include <stdio.h>
#include "trick/exec_proto.h"
class Wind
{
public:
    double Wforce[3];   /* kg.m/s^2 engine force */
    double magnitude;   /* kg.m/s^2 engine force magnitude*/
    double time;        /* s Model time */
    Wind();
    ~Wind(){};
    int default_data();
    int init(double forceX0, double forceY0, double forceZ0);
    int shutdown();
    double get_magnitude();
};

#endif
