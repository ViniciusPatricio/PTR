//
// Created by vinicius on 17/09/22.
//
#include <control.h>

Matrix cmalculate_atrix_Vt(Matrix YM_dot, Matrix YM, Matrix YT){
    Matrix Vt = matrix_constructor(2,1);
    Vt.values[0] = YM_dot.values[0] + Alpha1*(YM.values[0] - YT.values[0]);
    Vt.values[1] = YM_dot.values[1] = Alpha2*(YM.values[1] - YT.values[1]);
    return Vt;
}






