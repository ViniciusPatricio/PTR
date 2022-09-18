//
// Created by vinicius on 17/09/22.
//


#include <time.h>
#include "Matrix.h"
#include <ref_model.h>
#include <mutexes.h>

Matrix calculate_YM_dot(Matrix ref, Matrix YM){
    Matrix YM_dot =  matrix_constructor(2,1);
    YM_dot.values[0] = Alpha1*(ref.values[0] - YM.values[0]);
    YM_dot.values[1] = Alpha2*(ref.values[1] - YM.values[2]);
    return YM_dot;
}
// Integrando YM_DOT -> YM
Matrix calculate_YM(Matrix YM_dot, Matrix YM_dot_old,double delta){
    Matrix YM = matrix_constructor(2,1);

    YM.values[0] = delta*(YM_dot_old.values[0] + YM_dot.values[0])/2;
    YM.values[1] = delta*(YM_dot_old.values[1] + YM_dot.values[1])/2;

    return YM;
}

void *refModel_thread(void *){
    double t = 0;       //tempo calculado
    double tm = 0;      //tempo medido
    double T = 30;      //milissegundos
    struct timespec ts1, ts2, ts3={0};

    //Matrix ref;

    while(t <= 13000) {

        clock_gettime(CLOCK_REALTIME, &ts1);
        tm = 1000000 * ts1.tv_nsec - tm;
        t = t + T;

        //ref = calculate_reference(t/1000);
        //matrix_print(ref);

        clock_gettime(CLOCK_REALTIME, &ts2);
        ts3.tv_sec = 0;
        ts3.tv_nsec = T*1000000 - (ts2.tv_nsec - ts1.tv_nsec);

        nanosleep(&ts3, &ts3);
    }
}