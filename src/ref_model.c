//
// Created by vinicius on 17/09/22.
//

#include <ref_model.h>


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