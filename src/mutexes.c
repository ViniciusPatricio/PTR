//
// Created by vinicius on 17/09/22.
//
#include <pthread.h>

#include "Matrix.h"
#include "mutexes.h"

static Matrix Ref;
static Matrix Y;
static Matrix YM;
static Matrix YM_dot;
static Matrix Vt;
static Matrix Ut;
static Matrix X;
static Matrix X_dot;

static pthread_mutex_t mutexRef     = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t mutexY       = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t mutexYM      = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t mutexYM_dot  = PTHREAD_MUTEX_INITIALIZER;

void mutexes_init(){
   Ref      = matrix_zeros(2,1);
    Y       = matrix_zeros(2,1);
    YM      = matrix_zeros(2,1);
    YM_dot  = matrix_zeros(2,1);
    Vt      = matrix_zeros(2,1);
    Ut      = matrix_zeros(2,1);
    X       = matrix_zeros(3,1);
    X_dot   = matrix_zeros(3,1);
}

void mutexes_destoy(){
    pthread_mutex_destroy(&mutexRef);
    pthread_mutex_destroy(&mutexY);
    pthread_mutex_destroy(&mutexYM);
    pthread_mutex_destroy(&mutexYM_dot);
}

void mutexes_setRef(Matrix ref){
    pthread_mutex_lock(&mutexRef);
    Ref = ref;
    pthread_mutex_unlock(&mutexRef);
}

void mutexes_getRef(Matrix *ref){
    if(!ref) return;
    pthread_mutex_lock(&mutexRef);
    *ref = Ref;
    pthread_mutex_unlock(&mutexRef);
}

void mutexes_setYm(Matrix Ym){
    pthread_mutex_lock(&mutexYM);
    YM = Ym;
    pthread_mutex_unlock(&mutexYM);
}


void mutexes_setYm_dot(Matrix Ym_dot){

    pthread_mutex_lock(&mutexYM_dot);
    YM_dot = Ym_dot;
    pthread_mutex_unlock(&mutexYM_dot);

}
