//
// Created by vinicius on 19/09/22.
//
#include "stdio.h"
#include "jitters.h"
#include "math.h"

double calculate_latence(int  t, double ts_old){
    double ts = ((double) t/1000000);
    double dif_time = ts - ts_old;
    if(dif_time < 0){
        dif_time = ts + 1000 - ts_old;
    }
    return dif_time;
}

double calculate_jitter(int t, double ts_old, double T){
    return  calculate_latence(t,ts_old) - T;
}

