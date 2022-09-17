#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "Integral.h"
#include "ref.h"
#include "math.h"
#define delta 0.0001



int main() {
    Matrix test = calculate_reference(2);
    matrix_print(test);
    return 0;
}