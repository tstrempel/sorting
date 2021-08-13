#include <stdio.h>
#include <math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_blas.h>

#include "common_methods.h"

struct lgs_data lgs;


void jacobi_iteration() 
{
    gsl_matrix *D_inverse;  /* inverse Diagonalmatrix */
    gsl_permutation *p_inverse;  /* wird von GSL zur Berechnung dieser benötigt */
    int signum;

    gsl_matrix *L_plus_U;
    gsl_matrix *J;  /* Jacobi Matrix */
    gsl_vector *J_x;
    gsl_vector *c;  /* nicht iterativer Teil der Abbildung */
    int iterations = 0;  /* zählt wie viele Iterationen das verfahren benötigt*/
    
    create_A();
    create_b();
    create_x();
    create_LDU();
    create_x_prev();

    /* Inverse Matrix zur Diagonalmatrix berechnen 
     * D_inverse = D^-1
     */
    D_inverse = gsl_matrix_alloc(ROWS, COLS);  
    p_inverse = gsl_permutation_alloc(ROWS);  
    gsl_linalg_LU_decomp(lgs.D, p_inverse, &signum);
    gsl_linalg_LU_invert(lgs.D, p_inverse, D_inverse);

    /* L_plus_U = L + U */
    L_plus_U = gsl_matrix_alloc(ROWS, COLS);
    gsl_matrix_memcpy(L_plus_U, lgs.L);
    gsl_matrix_add(L_plus_U, lgs.U);

    /* c = D^-1 * b 
     * c = D_inverse * b
     */
    c = gsl_vector_alloc(ROWS);
    gsl_blas_dgemv(CblasNoTrans, 1.0, D_inverse, lgs.b, 0.0, c);


    /* Berechnung des neuen Lösungsvektors x */
    do {
        gsl_vector_memcpy(lgs.x_prev, lgs.x);

        /* J = -D^-1 * (L+U) 
         * J = -D_inverse * L_plus_U
         */
        J = gsl_matrix_alloc(ROWS, COLS);
        gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, 
            D_inverse, L_plus_U, 0.0, J);
        gsl_matrix_scale(J, -1.0);

        /* J_x = -D^-1 * (L+U) * x 
         * J_x = J * x
         */
        J_x = gsl_vector_alloc(ROWS);
        gsl_blas_dgemv(CblasNoTrans, 1.0, J, lgs.x, 0.0, J_x);

        /* x = -D^-1 * (L+U) * x + D^-1 * b 
         * x = J_x + c
         * Lösungsvektor x wird berechnet
         */
        gsl_vector_memcpy(lgs.x, J_x);
        gsl_vector_add(lgs.x, c);

        gsl_matrix_free(J);
        gsl_vector_free(J_x);
        iterations++;
    } while (!stop_iterating(iterations));

    printf("\n--------------------------------------------------\n\n");
    printf("\nTest erfolgreich nach %d Iterationen\n", iterations);

    gsl_matrix_free(D_inverse);
    gsl_matrix_free(L_plus_U);
    gsl_matrix_free(lgs.A);
    gsl_matrix_free(lgs.L);
    gsl_matrix_free(lgs.D);
    gsl_matrix_free(lgs.U);
    gsl_vector_free(lgs.b);
    gsl_vector_free(lgs.x);
    gsl_vector_free(lgs.x_prev);
    gsl_permutation_free(p_inverse);
}

int main(void) 
{
    jacobi_iteration();
    return 0;
}