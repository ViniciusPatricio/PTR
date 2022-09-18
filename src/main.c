#include <stdio.h>
#include <time.h>
#include <ref.h>
#include <ref_model.h>
#include <linear.h>
#include <mutexes.h>
#include <pthread.h>

int main() {
    mutexes_init();
    pthread_t TRef, TRef_model;

    pthread_create(&TRef, NULL, ref_thread(NULL),NULL);
    pthread_create(&TRef_model,NULL,refModel_thread(NULL),NULL);

    //pthread_join(TRef, NULL);
    //pthread_join(TRef_model, NULL);
    return 0;
}