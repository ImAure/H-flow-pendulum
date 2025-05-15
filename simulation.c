#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define STRLEN      1024
#define FILE_NAME   "H-flow-out.dat"

typedef struct point {
    double q;
    double p;
} point;
typedef FILE file;

point increment(double h, point state);

point euler(double h, point state);

int main(int argc, char *argv[6]) {
    point state;
    double time, step, t;
    file *pf;

    if (argc < 6) {
        printf("Usage: %s <path/to/file.dat> <time duration> <step duration> <initial q> <initial p>\n", argv[0]);
        return 1;
    }

    printf("Creating file %s\n", argv[1]);
    pf = fopen(argv[1], "w");
    if (pf == NULL) {
        printf("Error creating/opening file at %s\n", argv[1]);
        return 1;
    }
    
    if ((time = atof(argv[2])) <= 0) {
        printf("Time duration must be positive.\n");
        return 1;
    }

    if ((step = atof(argv[3])) <= 0) {
        printf("Time step must be positive.\n");
        return 1;
    }
    
    state.q = atof(argv[4]);
    state.p = atof(argv[5]);
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
    newstate.p = state.p - h * cos(state.q);
    return newstate;
}