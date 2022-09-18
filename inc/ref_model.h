
#define Alpha1 3
#define Alpha2 3

Matrix calculate_YM_dot(Matrix ref, Matrix YM);

Matrix calculate_YM(Matrix YM_dot, Matrix YM_dot_old, double delta);

void *refModel_thread(void *);