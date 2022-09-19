//
// Created by vinicius on 19/09/22.
//
#include "stdio.h"
#include "ref.h"
#include "ref_model.h"
#include "control.h"
#include "linear.h"
#include "robot.h"
#include "evaluate_model.h"
#include "math.h"

double mean(double jitter[], double T){
    double sum = 0;
    for(int i = 1; i < 14000/T;i++){
        sum += jitter[i];
    }
    return sum/(14000/T);
}

double max_min(double jitter[],double T, int op){
    double min = jitter[1];
    double max = jitter[1];
    for(int i = 1; i < (14000/T); i++){
        if(min > jitter[i]){
            min = jitter[i];
        }
        if(max < jitter[i]){
            max = jitter[i];
        }
    }
    if(op == 0){
        return min;
    }else{
        return max;
    }
}

double var_dp(double jitter[],double T, int op){
    double var = 0;
    double mean_calculate = mean(jitter,T);

    for(int i = 1; i < 14000/T;i++){
        var += pow((jitter[i]-mean_calculate),2);
    }
    var = var/(14000/T);
    if(op == 0){
        return var;
    }else{
        return sqrt(var);
    }
}

void evaluate(){
    double *jitters_ref; double *jitters_RefModel; double *jitters_Control; double *jitters_Linear; double *jitters_Robot;
    double  *latency_ref; double *latency_RefModel; double *latency_Control; double *latency_Linear; double *latency_Robot;

    jitters_ref = getJitter_ref(); latency_ref = getLatency_ref();
    jitters_RefModel = getJitter_Refmodel();jitters_Control = getJitter_Control();jitters_Linear = getJitter_Linear(); jitters_Robot = getJitter_Robot();
    latency_RefModel = getLatency_Refmodel(); latency_Control = getLatency_Control(); latency_Linear = getLatency_Linear(); latency_Robot = getLatency_Robot();

    FILE *file;

    //abrindo o arquivo
    file = fopen("evaluate.txt", "w");
    fprintf(file,"Ref      Ref_model     Control        Linear       Robot\n");
            fprintf(file,"%lf\t%lf\t%lf\t%lf\t%lf\n", mean(jitters_ref,50), mean(jitters_RefModel,30), mean(jitters_Control,30),
            mean(jitters_Linear,20), mean(jitters_Robot,10));
    fprintf(file,"%lf\t%lf\t%lf\t%lf\t%lf\n", var_dp(jitters_ref,50,0), var_dp(jitters_RefModel,30,0), var_dp(jitters_Control,30,0),
            var_dp(jitters_Linear,20,0), var_dp(jitters_Robot,10,0));
    fprintf(file,"%lf\t%lf\t%lf\t%lf\t%lf\n", var_dp(jitters_ref,50,1), var_dp(jitters_RefModel,30,1), var_dp(jitters_Control,30,1),
            var_dp(jitters_Linear,20,1), var_dp(jitters_Robot,10,1));
    fprintf(file,"%lf\t%lf\t%lf\t%lf\t%lf\n", max_min(jitters_ref,50,1), max_min(jitters_RefModel,30,1), max_min(jitters_Control,30,1),
            max_min(jitters_Linear,20,1), max_min(jitters_Robot,10,1));
    fprintf(file,"%lf\t%lf\t%lf\t%lf\t%lf\n", max_min(jitters_ref,50,0), max_min(jitters_RefModel,30,0), max_min(jitters_Control,30,0),
            max_min(jitters_Linear,20,0),max_min(jitters_Robot,10,0));

    fprintf(file,"\n\n%lf\t%lf\t%lf\t%lf\t%lf\n", mean(latency_ref,50), mean(latency_RefModel,30), mean(latency_Control,30),
            mean(latency_Linear,20), mean(latency_Robot,10));
    fprintf(file,"%lf\t%lf\t%lf\t%lf\t%lf\n", var_dp(latency_ref,50,0), var_dp(latency_RefModel,30,0), var_dp(latency_Control,30,0),
            var_dp(latency_Linear,20,0), var_dp(latency_Robot,10,0));
    fprintf(file,"%lf\t%lf\t%lf\t%lf\t%lf\n", var_dp(latency_ref,50,1), var_dp(latency_RefModel,30,1), var_dp(latency_Control,30,1),
            var_dp(latency_Linear,20,1), var_dp(latency_Robot,10,1));
    fprintf(file,"%lf\t%lf\t%lf\t%lf\t%lf\n", max_min(latency_ref,50,1), max_min(latency_RefModel,30,1), max_min(latency_Control,30,1),
            max_min(latency_Linear,20,1), max_min(latency_Robot,10,1));
    fprintf(file,"%lf\t%lf\t%lf\t%lf\t%lf\n", max_min(latency_ref,50,0), max_min(latency_RefModel,30,0), max_min(latency_Control,30,0),
            max_min(latency_Linear,20,0), max_min(latency_Robot,10,0));


    fclose(file);
}