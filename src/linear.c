//
// Created by vinicius on 17/09/22.
//
#include "Matrix.h"
#include "math.h"
#include "stdio.h"
#include "time.h"
#include "mutexes.h"
#include <linear.h>

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

    Matrix X, V, U;

    while(t <= 13000) {

        clock_gettime(CLOCK_REALTIME, &ts1);
        tm = 1000000 * ts1.tv_nsec - tm;
        t = t + T;
        mutexes_getX(&X);
        mutexes_getV(&V);

        U = calculate_Ut(X,V,Raio);
        mutexes_setU(U);
        //printf("%f,%f\n",U.values[0],U.values[1]);

        clock_gettime(CLOCK_REALTIME, &ts2);
        ts3.tv_sec = 0;
        ts3.tv_nsec = T*1000000 - (ts2.tv_nsec - ts1.tv_nsec);

        nanosleep(&ts3, &ts3);
    }
}