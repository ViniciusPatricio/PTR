//
// Created by vinicius on 17/09/22.
//
#include "stdio.h"
#include "Matrix.h"
#include "time.h"
#include <robot.h>
#include "math.h"
#include "mutexes.h"
#include "jitters.h"

#define N_ROBOT 14000/10

double jitters_Robot[N_ROBOT];
double latency_Robot[N_ROBOT];

double *getJitter_Robot(){
    return jitters_Robot;
}

double *getLatency_Robot(){
    return latency_Robot;
}

Matrix calculate_X_dot(Matrix Xt, Matrix                                                                                                                                                                                                                                                                                                                                                                                                                                                               Ut){
    Matrix aux = matrix_constructor(3,2);
    aux.values[0] = cos(Xt.values[2]); aux.values[1] = 0;
    aux.values[2] = sin(Xt.values[2]); aux.values[3] = 0;
    aux.values[4] = 0; aux.values[5] = 1;
    return matrix_mult(aux,Ut);
}

Matrix calculate_Xt(Matrix Xt_dot, Matrix Xt_dot_old, double delta){
    Matrix Xt = matrix_constructor(3,1);
    Xt.values[0] = delta*(Xt_dot.values[0] + Xt_dot_old.values[0])/2;
    Xt.values[1] = delta*(Xt_dot.values[1] + Xt_dot_old.values[1])/2;
    Xt.values[2] = delta*(Xt_dot.values[2] + Xt_dot_old.values[2])/2;
    return Xt;
}

Matrix calculate_Yt(Matrix Xt, double R){
    Matrix identity = matrix_identify(2,3);
    Matrix aux_result =  matrix_mult(identity,Xt);
    Matrix Yt = matrix_constructor(2,1);
    Yt.values[0] = (aux_result.values[0]+R*cos(Xt.values[2]));
    Yt.values[1] = (aux_result.values[1]+R*sin(Xt.values[2]));

    return Yt;
}

void *robot_thread(void *){
    double t = 0;       //tempo calculado
    double tm = 0;      //tempo medido
    double T = 10;      //milissegundos
    double Raio = 0.3;
    struct timespec ts1, ts2, ts3={0};
    double jitter = 0;
    double dif_time = 0;
    int indice = 0;
    Matrix X_dot_old, Ut, X_dot, X, X_old, Y;

    while(t <= 14000) {

        clock_gettime(CLOCK_REALTIME, &ts1);
        dif_time = calculate_latence(ts1.tv_nsec,tm);
        jitter = calculate_jitter(ts1.tv_nsec,tm,T);
        jitters_Robot[indice] = jitter;
        latency_Robot[indice] = dif_time;


        tm = (double) ts1.tv_nsec/1000000;
        t = t + T;
        indice++;


        mutexes_getX_dot(&X_dot_old);
        mutexes_getX(&X_old);
        mutexes_getU(&Ut);

        X_dot = calculate_X_dot(X_old,Ut);


        X = calculate_Xt(X_dot,X_dot_old,0.03);

        Y = calculate_Yt(X,Raio);

        mutexes_setX_dot(X_dot);
        mutexes_setX(X);
        mutexes_setY(Y);


        clock_gettime(CLOCK_REALTIME, &ts2);
        ts3.tv_sec = 0;
        ts3.tv_nsec = T*1000000 - (ts2.tv_nsec - ts1.tv_nsec);

        nanosleep(&ts3, &ts3);
    }

}