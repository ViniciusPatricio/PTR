
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <ref.h>
#include "mutexes.h"
#include "jitters.h"

#define N_REF 14000/50

double jitter_ref[N_REF];
double latency_ref[N_REF];

double *getJitter_ref(){
    return jitter_ref;
}

double *getLatency_ref(){
    return latency_ref;
}

Matrix calculate_reference(double t){
    Matrix matrix_ref;

    if( t < 0 && t > 4*M_PI){
        matrix_ref = matrix_zeros(2,1);
    }else if( t>= 0 && t < 2*M_PI){
        matrix_ref = matrix_constructor(2,1);
        matrix_ref.values[0] = 0.5 -0.5 *cos(t);
        matrix_ref.values[1] = 0.5 * sin(t);

    }else{
        matrix_ref = matrix_constructor(2,1);
        matrix_ref.values[0] = -0.5 + 0.5 * cos(t);
        matrix_ref.values[1] = -0.5 *sin(t);
    }

    return matrix_ref;
}

void *ref_thread(void *){

    double t = 0;       //tempo calculado
    double tm = 0;      //tempo medido
    double T = 50;      //milissegundos
    double dif_time = 0;
    double  jitter = 0;
    int indice = 0;
    struct timespec ts1, ts2, ts3={0};
    Matrix ref;
    double t_aux = 0;
    while(t <= 14000) {


        clock_gettime(CLOCK_REALTIME, &ts1);
        jitter = calculate_jitter(ts1.tv_nsec,tm,T);
        dif_time = calculate_latence(ts1.tv_nsec,tm);
        if(t != 0){
            t_aux += dif_time;
        }

        jitter_ref[indice] = jitter;
        latency_ref[indice] =dif_time;



        tm = (double) ts1.tv_nsec/1000000;


        t = t + T;
        indice++;

        ref = calculate_reference(t_aux/1000);
        mutexes_setRef(ref);

        clock_gettime(CLOCK_REALTIME, &ts2);
        ts3.tv_sec = 0;
        ts3.tv_nsec = T*1000000 - (ts2.tv_nsec - ts1.tv_nsec);

        nanosleep(&ts3, &ts3);
    }
}
