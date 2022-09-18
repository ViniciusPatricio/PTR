//
// Created by vinicius on 17/09/22.
//
#include <robot.h>
#include "math.h"

Matrix calculate_X_dot(Matrix Xt, Matrix Ut){
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
    Matrix result_aux = matrix_mult(Xt,identity);
    Matrix Yt = matrix_constructor(2,1);
    Yt.values[0] = (result_aux.values[0]+R*cos(Xt.values[2]));
    Yt.values[1] = (result_aux.values[1]+R*sin(Xt.values[2]));

    return Yt;
}