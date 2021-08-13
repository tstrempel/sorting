#include <stdio.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_statistics.h>

int main(void)
{
    /* declare variables */
    int i, j, rows, cols;
    gsl_matrix *m, *mm;
    gsl_vector *v;
    gsl_vector_view vv;
    FILE *f;

    rows=4; cols=3;
    m = gsl_matrix_alloc(rows, cols);  /* create a matrix */

    /* initialise a matrix */
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            gsl_matrix_set(m, i, j, 10.0*i+j);
        }
    }

    /* print matrix the hard way */
    printf("Matrix m\n");
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            printf("%f ", gsl_matrix_get(m, i, j));
        }
        printf("\n");
    }
    printf("\n");

    /* read in a matrix from a file */
    mm = gsl_matrix_alloc(rows, cols);
    f = fopen("gsl_test_matvec.txt", "r");
    gsl_matrix_fscanf(f, mm);
    fclose(f);

    /* print matrix the easy way */
    printf("Matrix mm\n");
    gsl_matrix_fprintf(stdout, mm, "%f");

    /* put column means into a vector */
    v = gsl_vector_alloc(cols);
    for (i = 0; i < cols; i++)
    {
        vv = gsl_matrix_column(mm, i);
        printf("\nCol %d\n", i);
        gsl_vector_fprintf(stdout, &vv.vector, "%f");
        gsl_vector_set(v, i, gsl_stats_mean(
            vv.vector.data, vv.vector.stride, vv.vector.size));
    }

    /* print column means */
    printf("\nColumn means\n");
    gsl_vector_fprintf(stdout, v, "%f");
    /* print overall mean */
    printf("\nOverall mean\n");
    printf("%f\n", gsl_stats_mean(v->data, v->stride, v->size));

    /* release memory */
    gsl_matrix_free(m);
    gsl_matrix_free(mm);
    gsl_vector_free(v);
    return(0);
}