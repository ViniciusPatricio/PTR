#include <stdio.h>
#include <time.h>
#include <ref.h>
#include <ref_model.h>
#include "control.h"
#include <linear.h>
#include <mutexes.h>
#include <pthread.h>

int main() {
    mutexes_init();
    pthread_t TRef, TRef_model, Tcontrol;

    pthread_create(&TRef, NULL, ref_thread,NULL);
    pthread_create(&TRef, NULL, refModel_thread,NULL);
    pthread_create(&Tcontrol, NULL,control_thread,NULL);

    pthread_join(TRef, NULL);
    pthread_join(TRef_model, NULL);
    return 0;
}