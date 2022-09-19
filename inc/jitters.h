

double calculate_latencey(int  t, double ts_old);
double calculate_jitter(int t, double ts_old, double T);
double mean_jitter(double jitter[], double T);
double max_min_jitter(double jitter[],double T, int op);
double var_dp_jitter(double jitter[],double T, int op);
