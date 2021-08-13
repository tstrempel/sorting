#ifndef COMMON_METHODS_H
#define COMMON_METHODS_H

#include <gsl/gsl_matrix.h>

#define ROWS 4
#define COLS 4

struct lgs_data {
    gsl_matrix *A;
    gsl_matrix *L;
    gsl_matrix *D;
    gsl_matrix *U;
    gsl_vector *b;
    gsl_vector *x;
    gsl_vector *x_prev;
};

void create_A();
void create_b();
void create_x();
void create_LDU();
void create_x_prev();
int stop_iterating(int iterations);
void print_vector(gsl_vector *vec);

#endif