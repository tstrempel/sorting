#include <math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_blas.h>

#include "common_methods.h"

/* struct, welches alle relevanten und übergreifenden Matritzen und Vektoren beinhaltet */
struct lgs_data _lgs;

/* Ausgangsmatrix A anhand des gegebenen Gleichungssystems erstellen */
void create_A() 
{
    _lgs.A = gsl_matrix_alloc(ROWS, COLS);
    gsl_matrix_set(_lgs.A, 0, 0, 10.0);
    gsl_matrix_set(_lgs.A, 0, 1, -1.0);
    gsl_matrix_set(_lgs.A, 0, 2, 2.0);
    gsl_matrix_set(_lgs.A, 0, 3, 0.0);
    
    gsl_matrix_set(_lgs.A, 1, 0, -1.0);
    gsl_matrix_set(_lgs.A, 1, 1, 11.0);
    gsl_matrix_set(_lgs.A, 1, 2, -1.0);
    gsl_matrix_set(_lgs.A, 1, 3, 3.0);

    gsl_matrix_set(_lgs.A, 2, 0, 2.0);
    gsl_matrix_set(_lgs.A, 2, 1, -1.0);
    gsl_matrix_set(_lgs.A, 2, 2, 10.0);
    gsl_matrix_set(_lgs.A, 2, 3, -1.0);

    gsl_matrix_set(_lgs.A, 3, 0, 0.0);
    gsl_matrix_set(_lgs.A, 3, 1, 3.0);
    gsl_matrix_set(_lgs.A, 3, 2, -1.0);
    gsl_matrix_set(_lgs.A, 3, 3, 8.0);
}

/* Ausgangsvektor b anhand des gegebenen Gleichungssystems erstellen */
void create_b() 
{
    _lgs.b = gsl_vector_alloc(ROWS);
    gsl_vector_set(_lgs.b, 0, 6.0);
    gsl_vector_set(_lgs.b, 1, 25.0);
    gsl_vector_set(_lgs.b, 2, -11.0);
    gsl_vector_set(_lgs.b, 3, 15.0);
}

/* Der Lösungsvektor x wird erstellt,
 * die Ausgangswerte entsprechen den Werten des Vektors b.
 */
void create_x() 
{
    _lgs.x = gsl_vector_alloc(ROWS);
    gsl_vector_set(_lgs.x, 0, 6.0);
    gsl_vector_set(_lgs.x, 1, 25.0);
    gsl_vector_set(_lgs.x, 2, -11.0);
    gsl_vector_set(_lgs.x, 3, 15.0);
}

/* Erstellung der strikten unteren Dreiecksmatrix L (für lower), der Diagonalmatrix D und der strikten oberen Dreiecksmatrix U (für upper) */
void create_LDU() 
{
    int i, j;
    _lgs.D = gsl_matrix_calloc(ROWS, COLS);
    _lgs.L = gsl_matrix_calloc(ROWS, COLS);
    _lgs.U = gsl_matrix_calloc(ROWS, COLS);

    /* Diagonalmatrix D */
    for (i = 0; i < 4; i++) {
        gsl_matrix_set(_lgs.D, i, i, gsl_matrix_get(_lgs.A, i, i));
    } 
    
    /* strikte untere Dreiecksmatrix L */
    for (i = 1; i < 4; i++) {
        for (j = 0; j < i; j++) {
            gsl_matrix_set(_lgs.L, i, j, gsl_matrix_get(_lgs.A, i, j));
        }
    }

    /* strikte obere Dreiecksmatrix U */
    for (i = 0; i < 3; i++) {
        for (j = 3; j > i; j--) {
            gsl_matrix_set(_lgs.U, i, j, gsl_matrix_get(_lgs.A, i, j));
        }
    }
}

/* Erstellen eines Vektors der die Werte des vorherigen Lösungsvektors x enthält,
 * um später die Maximumsnorm zu berechnen.
 */
void create_x_prev()
{
    _lgs.x_prev = gsl_vector_alloc(ROWS);
    gsl_vector_memcpy(_lgs.x_prev, _lgs.x);
}

/* Aufgabe 5: Stoppt die Iteration wenn die Maximumsnorm kleiner als 0.001 ist. */
int stop_iterating(int iterations)
{
    int i;
    double temp;
    double maximum_metric;  /* Maximumsnorm */
    gsl_vector *vec;
    
    print_vector(_lgs.x);  /* Ausgabe des derzeitigen Lösungsvektors x */
    printf("Iteration Nummer %d\n", iterations);

    /* Subtrahieren der Vektoren x^k und x^(k-1) */
    vec = gsl_vector_alloc(ROWS);
    gsl_vector_memcpy(vec, _lgs.x);
    gsl_vector_sub(vec, _lgs.x_prev);

    /* Berechnung der Maximumsnorm, indem der betragsmäßig größte Wert des Vektors gesucht wird */
    temp = fabs(gsl_vector_get(vec, 0));
    for (i = 1; i < ROWS; i++) {
        if (fabs(gsl_vector_get(vec, i)) > temp) {
            temp = fabs(gsl_vector_get(vec, i));
        }
    }
    maximum_metric = temp;

    printf("Maximumsnorm: %f", maximum_metric);

    if (maximum_metric > 0.001) {
        printf("\nTest erfolglos!\n");
        return 0;
    } else {
        printf("\nTest erfolgreich!\n");
        return 1;
    }
}

/* verschönerte Vektorausgabe */
void print_vector(gsl_vector* vec) 
{
    int i = 0;
    printf("\n--------------------------------------------------\n\nLösungsvektor x:\n");
    
    for (i = 0; i < vec->size; i++) {
        printf("x%d: \t%f\n", i+1, gsl_vector_get(vec, i));
    }
}