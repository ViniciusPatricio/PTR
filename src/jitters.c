//
// Created by vinicius on 19/09/22.
//
#include "stdio.h"
#include "jitters.h"
#include "math.h"

double calculate_latencey(int  t, double ts_old){
    double ts = ((double) t/1000000);
    double dif_time = ts - ts_old;
    if(dif_time < 0){
        dif_time = ts + 1000 - ts_old;
    }
    return dif_time;
}

double calculate_jitter(int t, double ts_old, double T){
    return  calculate_latencey(t,ts_old) - T;
}

double mean_jitter(double jitter[], double T){
    double sum = 0;
    for(int i = 1; i < 14000/T;i++){
        sum += jitter[i];
    }
    return sum/(14000/T);
}

double max_min_jitter(double jitter[],double T, int op){
    double min = jitter[1];
    double max = jitter[1];
    for(int i = 1; i < 14000/T; i++){
        if(min > jitter[i]){
            min = jitter[i];
        }
        if(max < jitter[i]){
            max = jitter[i];
        }
    }
    if(op == 0){
        return min;
    }else{
        return max;
    }
}

double var_dp_jitter(double jitter[],double T, int op){
    double var = 0;
    double mean = mean_jitter(jitter,T);

    for(int i = 1; i < 14000/T;i++){
        var += pow((jitter[i]-mean),2);
    }

}