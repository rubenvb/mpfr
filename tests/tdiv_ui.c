#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "gmp.h"
#include "mpfr.h"
#include "mpfr-impl.h"
#include "time.h"

extern int isnan(), getpid();

void check(double d, unsigned long u, unsigned char rnd)
{
  mpfr_t x, y; double e, f;

  mpfr_init2(x, 53); mpfr_init2(y, 53);
  mpfr_set_machine_rnd_mode(rnd);
  e = d / u;
  mpfr_set_d(x, d, rnd); 
  mpfr_div_ui(y, x, u, rnd); 
  f = mpfr_get_d(y);
  if (f != e && (!isnan(f) || !isnan(e))) {
    printf("mpfr_div_ui failed for x=%1.20e, u=%lu, rnd=%d\n",d,u,rnd);
    printf("expected result is %1.20e, got %1.20e, dif=%d ulp\n",e,f,
	   ulp(e,f));
    exit(1);
  }
  mpfr_clear(x); 
}

int
main(int argc, char **argv)
{
  int i; unsigned long u; double d;

  srand(getpid());
  check(1.0, 3, 0);
  check(1.0, 3, 1);
  check(1.0, 3, 2);
  check(1.0, 3, 3);
  check(1.0, 2116118, 0);
  for (i=0;i<1000000;i++) {
    do { u = lrand48(); } while (u==0);
    do { d = drand(); } while (fabs(d/u)<2.2e-307);
    check(d, u, rand() % 4);
  }
  return 0;
}
