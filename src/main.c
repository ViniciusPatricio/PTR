#include <stdio.h>
#include <time.h>
#include <ref.h>
#include <ref_model.h>
#include <control.h>
#include <robot.h>
#include <linear.h>
#include <mutexes.h>
#include <pthread.h>



void *print_thread( void *){
    double t = 0;       //tempo calculado
    double tm = 0;      //tempo medido
    double T = 100;      //milissegundos

    struct timespec ts1, ts2, ts3={0};

    Matrix Ref,Ym,Ym_dot,V,Ut,X_dot,X,Y;

    while(t <= 14000) {
        clock_gettime(CLOCK_REALTIME, &ts1);
        tm = 1000000 * ts1.tv_nsec - tm;
        t = t + T;

        mutexes_getRef(&Ref);
        mutexes_getYm(&Ym);
        mutexes_getYm_dot(&Ym_dot);
        mutexes_getV(&V);
        mutexes_getU(&Ut);
        mutexes_getX_dot(&X_dot);
        mutexes_getX(&X);
        mutexes_getY(&Y);

        printf("%f,",t);
        printf("%f,%f",Ref.values[0],Ref.values[1]);
        printf(",%f,%f",Ym.values[0],Ym.values[1]);
        printf(",%f,%f",Ym_dot.values[0],Ym_dot.values[1]);
        printf(",%f,%f",V.values[0],V.values[1]);
        printf(",%f,%f",Ut.values[0],Ut.values[1]);
        printf(",%f,%f,%f",X_dot.values[0],X_dot.values[1],X_dot.values[2]);
        printf(",%f,%f,%f",X.values[0],X.values[1],X.values[2]);
        printf(",%f,%f\n",Y.values[0],Y.values[1]);

        clock_gettime(CLOCK_REALTIME, &ts2);
        ts3.tv_sec = 0;
        ts3.tv_nsec = T*1000000 - (ts2.tv_nsec - ts1.tv_nsec);
        nanosleep(&ts3, &ts3);
    }
}




int main() {
    mutexes_init();
    pthread_t TRef, TRef_model, TControl, TLinear,TRobot,TPrint;

    pthread_create(&TRef, NULL, ref_thread,NULL);
    pthread_create(&TRef, NULL, refModel_thread,NULL);
    pthread_create(&TControl, NULL,control_thread,NULL);
    pthread_create(&TLinear, NULL,linear_thread,NULL);
    pthread_create(&TRobot, NULL,robot_thread,NULL);
    //pthread_create(&TPrint,NULL,print_thread,NULL);

    pthread_join(TRef, NULL);
    pthread_join(TRef_model, NULL);
    pthread_join(TControl, NULL);
    pthread_join(TLinear, NULL);
    pthread_join(TRobot, NULL);
    //pthread_join(TPrint,NULL);

    return 0;
}