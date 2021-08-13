#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>

#include "common_methods.h"

struct lgs_data lgs;

void gauss_seidel_iteration()
{
    gsl_matrix *D_plus_L;
    gsl_matrix *D_plus_L_inverse;
    gsl_permutation *p_DL_inverse;
    int signum_DL;

    gsl_vector *c;  /* nicht iterativer Teil der Abbildung */
    gsl_matrix *H_1;  /* Gauß-Seidel Matrix */
    int iterations = 0;

    gsl_vector *H_1_x;

    create_A();
    create_b();
    create_LDU();
    create_x();
    create_x_prev();

    /* Berechnung der Iterationsmatrix H_1 und des konstanten Anteils c */

    /* D_plus_L = D + L */
    D_plus_L = gsl_matrix_alloc(4, 4);
    gsl_matrix_memcpy(D_plus_L, lgs.D);
    gsl_matrix_add(D_plus_L, lgs.L);

    /* D_plus_L_inverse = (D+L)^-1 
     * D_plus_L_inverse = D_plus_L^-1
     */
    D_plus_L_inverse = gsl_matrix_alloc(4, 4);
    p_DL_inverse = gsl_permutation_alloc(4);  
    gsl_linalg_LU_decomp(D_plus_L, p_DL_inverse, &signum_DL);
    gsl_linalg_LU_invert(D_plus_L, p_DL_inverse, D_plus_L_inverse);

    /* c = (D+L)^-1 * b 
     * c = D_plus_L_inverse * b
     */
    c = gsl_vector_alloc(4);
    gsl_blas_dgemv(CblasNoTrans, 1.0, D_plus_L_inverse, lgs.b, 0.0, c);   

    /* H_1 = -(D+L)^-1 * U 
     * H_1 = -D_plus_L_inverse * U
     */
    gsl_matrix_scale(D_plus_L_inverse, -1.0);  /* Matrix negieren */
    H_1 = gsl_matrix_alloc(4, 4);
    gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, D_plus_L_inverse, 
        lgs.U, 0.0, H_1);

    /* Berechnung des neuen Lösungsvektors x */
    do {
        gsl_vector_memcpy(lgs.x_prev, lgs.x);

        /* H_1_x = -(D+L)^-1 * U * x
         * H_1_x = H_1 * x
         */
        H_1_x = gsl_vector_alloc(4);
        gsl_blas_dgemv(CblasNoTrans, 1.0, H_1, lgs.x, 0.0, H_1_x);

        /* x = -(D+L)^-1 * U * x + (D+L)^-1 * b 
         * x = H_1_x + c
         * Lösungsvektor x wird berechnet
         */
        gsl_vector_memcpy(lgs.x, H_1_x);
        gsl_vector_add(lgs.x, c);


        gsl_vector_free(H_1_x);
        iterations++;
    } while (!stop_iterating(iterations));
    
    printf("\n--------------------------------------------------\n\n");
    printf("\nTest erfolgreich nach %d Iterationen\n", iterations);
    
    gsl_matrix_free(D_plus_L);
    gsl_matrix_free(D_plus_L_inverse);
    gsl_matrix_free(H_1);
    gsl_vector_free(c);
    gsl_permutation_free(p_DL_inverse);
}

int main(void)
{
    gauss_seidel_iteration();
    return 0;
}