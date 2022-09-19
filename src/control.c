//
// Created by vinicius on 17/09/22.
//

#include <Matrix.h>
#include "stdio.h"
#include <control.h>
#include "time.h"
#include "mutexes.h"
#include "jitters.h"

#define N_Control 14000/30

double jitter_Control[N_Control];

#define Alpha1 3
#define Alpha2 3


Matrix calculate_atrix_Vt(Matrix YM_dot, Matrix YM, Matrix YT){
    Matrix Vt = matrix_constructor(2,1);
    Vt.values[0] = YM_dot.values[0] + Alpha1*(YM.values[0] - YT.values[0]);
    Vt.values[1] = YM_dot.values[1] + Alpha2*(YM.values[1] - YT.values[1]);
    return Vt;
}

void *control_thread(void *){
    double t = 0;       //tempo calculado
    double tm = 0;      //tempo medido
    double T = 30;      //milissegundos
    struct timespec ts1, ts2, ts3={0};
    double jitter = 0;
    int indice = 0;
    Matrix V,Ym_dot,Ym,Y;

    while(t <= 14000) {
        clock_gettime(CLOCK_REALTIME, &ts1);

        jitter = calculate_jitter(ts1.tv_nsec,tm,T);
        jitter_Control[indice] = jitter;
        tm = (double) ts1.tv_nsec/1000000;
        t = t + T;
        indice++;
        mutexes_getYm_dot(&Ym_dot);
        mutexes_getYm(&Ym);
        mutexes_getY(&Y);

        V = calculate_atrix_Vt(Ym_dot,Ym,Y);
        mutexes_setV(V);


        clock_gettime(CLOCK_REALTIME, &ts2);
        ts3.tv_sec = 0;
        ts3.tv_nsec = T*1000000 - (ts2.tv_nsec - ts1.tv_nsec);
        nanosleep(&ts3, &ts3);
    }

}









