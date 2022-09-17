//
// Created by vinicius on 17/09/22.
//

#include <linear.h>
Matrix calculate_Ut(Matrix Xt, Matrix Vt, double R){
    Matrix L = matrix_constructor(2,2);
    L.values[0] = cos(Xt.values[2]); L.values[1] = -R*sin(Xt.values[2]);
    L.values[2] = sin(Xt.values[2]); L.values[3] = R*cos(Xt.values[2]);
    return L;
};


