//
// Created by vinicius on 17/09/22.
//
#include "Matrix.h"
#include "math.h"
#include "stdio.h"
#include "time.h"
#include "mutexes.h"
#include "jitters.h"
#include <linear.h>


#define N_LINEAR 14000/20

double jitter_Linear[N_LINEAR];
double latency_Linear[N_LINEAR];

double *getJitter_Linear(){
    return jitter_Linear;
}

double *getLatency_Linear(){
    return latency_Linear;
}

Matrix calculate_Ut(Matrix Xt, Matrix Vt, double R){
    Matrix L = matrix_constructor(2,2);
    L.values[0] = cos(Xt.values[2]); L.values[1] = -R*sin(Xt.values[2]);
    L.values[2] = sin(Xt.values[2]); L.values[3] = R*cos(Xt.values[2]);
    Matrix L_inverse = matrix_inverse(L);
    return matrix_mult(L_inverse,Vt);
};


void *linear_thread( void *){
    double t = 0;       //tempo calculado
    double tm = 0;      //tempo medido
    double T = 20;      //milissegundos
    struct timespec ts1, ts2, ts3={0};
    double Raio = 0.3;
    double dif_time = 0;
    double jitter = 0;
    int indice = 0;
    Matrix X, V, U;

    while(t <= 14000) {

        clock_gettime(CLOCK_REALTIME, &ts1);
        dif_time = calculate_latence(ts1.tv_nsec,tm);
        jitter = calculate_jitter(ts1.tv_nsec,tm,T);
        jitter_Linear[indice] = jitter;
        latency_Linear[indice] = dif_time;
        tm = (double) ts1.tv_nsec/1000000;
        t = t + T;
        indice++;

        mutexes_getX(&X);
        mutexes_getV(&V);

        U = calculate_Ut(X,V,Raio);
        mutexes_setU(U);


        clock_gettime(CLOCK_REALTIME, &ts2);
        ts3.tv_sec = 0;
        ts3.tv_nsec = T*1000000 - (ts2.tv_nsec - ts1.tv_nsec);

        nanosleep(&ts3, &ts3);
    }

}