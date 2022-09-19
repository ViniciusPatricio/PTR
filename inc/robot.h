

Matrix calculate_X_dot(Matrix Xt, Matrix Ut);
Matrix calculate_Xt(Matrix Xt_dot, Matrix Xt_dot_old, double delta);
Matrix calculate_Yt(Matrix Xt, double R);
void *robot_thread(void *);
double *getJitter_Robot();
double *getLatency_Robot();