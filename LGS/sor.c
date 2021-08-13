#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_eigen.h>

#include "common_methods.h"

struct lgs_data lgs;

void sor_iteration()
{
    double relaxation_parameter = 1.050134773;
    gsl_matrix *omega_L;
    gsl_matrix *D_omega_L;
    gsl_matrix *left_factor;
    int signum1;
    gsl_permutation *permutation1;
    gsl_matrix *minus_omega_D;
    gsl_matrix *omega_U;
    gsl_matrix *right_factor;
    gsl_matrix *H_w;
    gsl_matrix *omega_D_omega_L_inverse;
    gsl_vector *c;
    gsl_vector *H_w_x;
    int iterations = 0;

    create_A();
    create_b();
    create_x();
    create_LDU();
    create_x_prev();

    /* Berechnung der Iterationsmatrix H_w und des konstanten Anteils c */

    /* omega_L = omega * L */
    omega_L = gsl_matrix_alloc(ROWS, COLS);
    gsl_matrix_memcpy(omega_L, lgs.L);
    gsl_matrix_scale(omega_L, relaxation_parameter);

    /* D_omega_L = D + omega * L 
     * D_omega_L = D + omega_L
     */
    D_omega_L = gsl_matrix_alloc(ROWS, COLS);
    gsl_matrix_memcpy(D_omega_L, lgs.D);
    gsl_matrix_add(D_omega_L, omega_L);

    /* left_factor = (D + omega * L)^-1 
     * left_factor = D_omega_L^-1
     */
    left_factor = gsl_matrix_alloc(ROWS, COLS);
    permutation1 = gsl_permutation_alloc(ROWS);
    gsl_linalg_LU_decomp(D_omega_L, permutation1, &signum1);
    gsl_linalg_LU_invert(D_omega_L, permutation1, left_factor);


    /* minus_omega_D = (1-omega) * D */
    minus_omega_D = gsl_matrix_alloc(ROWS, COLS);
    gsl_matrix_memcpy(minus_omega_D, lgs.D);
    gsl_matrix_scale(minus_omega_D, 1-relaxation_parameter);

    /* omega_U = omega * U */
    omega_U = gsl_matrix_alloc(ROWS, COLS);
    gsl_matrix_memcpy(omega_U, lgs.U);
    gsl_matrix_scale(omega_U, relaxation_parameter);

    /* right_factor = (1-omega) * D - omega * U 
     * right_factor = minus_omega_D - omega_U
     */
    right_factor = gsl_matrix_alloc(ROWS, COLS);
    gsl_matrix_memcpy(right_factor, minus_omega_D);
    gsl_matrix_sub(right_factor, omega_U);

    /* H_w = left_factor * right_factor */
    H_w = gsl_matrix_alloc(ROWS, COLS);
    gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, 
        left_factor, right_factor, 0.0, H_w);

    
    /* c berechnen */

    /* omega_D_omega_L_inverse = omega * (D+omega*L)^-1 * b 
     * omega_D_omega_L_inverse = omega * left_factor
     */
    omega_D_omega_L_inverse = gsl_matrix_alloc(ROWS, COLS);
    gsl_matrix_memcpy(omega_D_omega_L_inverse, left_factor);
    gsl_matrix_scale(omega_D_omega_L_inverse, relaxation_parameter);

    /* c = omega * (D+omega*L)^-1 * b 
     * c = omega_D_omega_L_inverse * b
     */
    c = gsl_vector_alloc(ROWS);
    gsl_blas_dgemv(CblasNoTrans, 1.0, omega_D_omega_L_inverse, lgs.b, 0.0, c);

    /* Berechnung des neuen Lösungsvektors x */
    do {
        /* H_w_x = H_w * x */
        gsl_vector_memcpy(lgs.x_prev, lgs.x);
        H_w_x = gsl_vector_alloc(ROWS);
        gsl_blas_dgemv(CblasNoTrans, 1.0, H_w, lgs.x, 0.0, H_w_x);
        
        /* x = H_w_x + c */
        gsl_vector_memcpy(lgs.x, H_w_x);
        gsl_vector_add(lgs.x, c);

        gsl_vector_free(H_w_x);
        iterations++;
    } while (!stop_iterating(iterations));

    printf("\n--------------------------------------------------\n\n");
    printf("\nTest erfolgreich nach %d Iterationen\n", iterations);

    gsl_matrix_free(omega_L);
    gsl_matrix_free(D_omega_L);
    gsl_matrix_free(left_factor);
    gsl_permutation_free(permutation1);
    gsl_matrix_free(minus_omega_D);
    gsl_matrix_free(omega_U);
    gsl_matrix_free(right_factor);
    gsl_matrix_free(H_w);
    gsl_matrix_free(omega_D_omega_L_inverse);
    gsl_vector_free(c);
}

int main(void)
{
    sor_iteration();
    return 0;
}