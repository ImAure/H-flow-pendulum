#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define STRLEN  1024

typedef struct point {
    double q;
    double p;
} point;

point increment(double h, point state);

int main(void) {
    char buffer[STRLEN];
    point state;
    double step;

    state = increment(step, state);

}

point increment(double h, point state) {
    point newstate;
    newstate.q = state.q + h * state.p;
    newstate.p = state.p - h * cos(state.q);
    return newstate;
}