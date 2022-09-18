#include <stdio.h>
#include <time.h>
#include <ref.h>
#include <ref_model.h>
#include <control.h>
#include <robot.h>
#include <linear.h>
#include <mutexes.h>
#include <pthread.h>

int main() {
    mutexes_init();
    pthread_t TRef, TRef_model, TControl, TLinear,TRobot;

    pthread_create(&TRef, NULL, ref_thread,NULL);
    pthread_create(&TRef, NULL, refModel_thread,NULL);
    pthread_create(&TControl, NULL,control_thread,NULL);
    pthread_create(&TLinear, NULL,linear_thread,NULL);
    pthread_create(&TRobot, NULL,robot_thread,NULL);

    pthread_join(TRef, NULL);
    pthread_join(TRef_model, NULL);
    pthread_join(TControl, NULL);
    pthread_join(TLinear, NULL);
    pthread_join(TRobot, NULL);
    return 0;
}