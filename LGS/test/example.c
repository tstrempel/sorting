#include <stdio.h>
#include <gsl/gsl_sf_bessel.h>

// gcc -L/usr/local/lib example.o -lgsl -lgslcblas -lm
int
main (void)
{
  double x = 5.0;
  double y = gsl_sf_bessel_J0 (x);
  printf ("J0(%g) = %.18e\n", x, y);
  return 0;
}