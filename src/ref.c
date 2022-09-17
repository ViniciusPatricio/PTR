
#include <math.h>
#include <time.h>
#include <ref.h>


Matrix calculate_reference(double t){
    Matrix matrix_ref;

    if( t < 0 && t > 4*M_PI){
        matrix_ref = matrix_zeros(2,1);
    }else if( t>= 0 && t < 2*M_PI){
        matrix_ref = matrix_constructor(2,1);
        matrix_ref.values[0] = 0.5 -0.5 *cos(t);
        matrix_ref.values[1] = 0.5 * sin(t);

    }else{
        matrix_ref = matrix_constructor(2,1);
        matrix_ref.values[0] = -0.5 + 0.5 * cos(t);
        matrix_ref.values[1] = -0.5 *sin(t);
    }

    return matrix_ref;
}
