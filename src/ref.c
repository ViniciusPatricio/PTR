
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <ref.h>
#include "mutexes.h"
#include "jitters.h"

#define N_REF 14000/50

double jitter_ref[N_REF];

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

    while(t <= 14000) {

        clock_gettime(CLOCK_REALTIME, &ts1);

        dif_time = calculate_latencey(ts1.tv_nsec,tm);
        jitter = calculate_jitter(ts1.tv_nsec,tm,T);
        jitter_ref[indice] = jitter;
        tm = (double) ts1.tv_nsec/1000000;

        printf("indice: %d dif_time: %f jitter: %f  armazenando jitter: %f\n",indice,dif_time,jitter,jitter_ref[indice]);
        t = t + T;
        indice++;

        ref = calculate_reference(t/1000);
        mutexes_setRef(ref);

        clock_gettime(CLOCK_REALTIME, &ts2);
        ts3.tv_sec = 0;
        ts3.tv_nsec = T*1000000 - (ts2.tv_nsec - ts1.tv_nsec);

        nanosleep(&ts3, &ts3);
    }
}
