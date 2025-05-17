#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ARG_NUM 6

typedef FILE file;
typedef struct point {
    double q;
    double p;
} point;

point euler(double h, point state);

int main(int argc, char *argv[ARG_NUM]) {
    point state;
    double time, step, t;
    file *pf;

    if (argc < ARG_NUM) {
        printf("Usage: %s <path/to/file.dat> <time duration> <step duration> <initial q> <initial p>\n", argv[0]);
        return 1;
    }

    printf("Creating file %s\n", argv[1]);
    pf = fopen(argv[1], "w");
    time = atof(argv[2]);
    step = atof(argv[3]);
    state.q = atof(argv[4]);
    state.p = atof(argv[5]);

    if (pf == NULL) {
        printf("Error creating/opening file at %s\n", argv[1]);
        return 1;
    }
    
    if ((time <= 0) || (step <= 0)) {
        printf("All time durations must be positive.\n");
        return 1;
    } 
    
    if (state.q < -M_PI || state.q > M_PI) {
        printf("Initial q must be in the range [-π, π].\n");
        return 1;
    }
    
    for (t = 0; t < time; t += step) {
        fprintf(pf, "%lf %lf %lf\n", t, state.q, state.p);
        state = euler(step, state);
    }
    fprintf(pf, "%lf %lf %lf", t, state.q, state.p);

    fclose(pf);
    printf("Simulation completed. Data written to %s\n", argv[1]);
    return 0;
}

point euler(double h, point state) {
    point newstate;
    newstate.q = state.q + h * state.p;
    newstate.p = state.p - h * sin(state.q);
    return newstate;
}