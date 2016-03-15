#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <gmp.h>
#include <mpfr.h>

/* Note: It may be useful to check with precy slightly different from precx
 * because mpfr_add has a special optimization when all the precisions are
 * the same.
 */

typedef int (*sumf) (mpfr_ptr, mpfr_ptr *const, unsigned long, mpfr_rnd_t);

static sumf fp[3] = { mpfr_sum, mpfr_sum_new, mpfr_sum_add };
static char *fn[3] = { "sum_old", "sum_new", "sum_add" };

static void
check_random (mpfr_rnd_t r, long n, long nc,
              mpfr_prec_t precx, mpfr_prec_t precs,
              unsigned long emax, long ntests, unsigned long seed)
{
  mpfr_t *x, s[3];
  mpfr_ptr *p;
  long i, j;
  gmp_randstate_t state;
  clock_t c;

  gmp_randinit_default (state);
  gmp_randseed_ui (state, seed);

  for (i = 0; i < 3; i++)
    mpfr_init2 (s[i], precs);

  x = (mpfr_t *) malloc (n * sizeof (mpfr_t));
  p = (mpfr_ptr *) malloc (n * sizeof (mpfr_ptr));
  for (i = 0; i < n; i++)
    {
      mpfr_init2 (x[i], precx);
      if (i < n - nc)
        {
          mpfr_urandom (x[i], state, r);
          if (gmp_urandomm_ui (state, 2))
            mpfr_neg (x[i], x[i], MPFR_RNDN);
          mpfr_mul_2ui (x[i], x[i], gmp_urandomm_ui (state, emax), MPFR_RNDN);
        }
      else
        {
          mpfr_sum_new (x[i], p, i, MPFR_RNDN);
          mpfr_neg (x[i], x[i], MPFR_RNDN);
          if (mpfr_zero_p (x[i]))
            {
              /* Stop here as it is not very useful to fill the array
                 with zeros. */
              mpfr_clear (x[i]);
              n = i;
              break;
            }
        }
      p[i] = x[i];
    }

  if (nc)  /* random permutation with 2*n random transpositions */
    for (i = 0; i < 2*n; i++)
      {
        int i1, i2;
        i1 = gmp_urandomm_ui (state, n);
        i2 = gmp_urandomm_ui (state, n);
        mpfr_swap (x[i1], x[i2]);
      }

  for (i = 0; i < 3; i++)
    {
      c = clock ();
      for (j = 0; j < ntests; j++)
        fp[i] (s[i], p, n, r);
      c = clock () - c;
      mpfr_printf ("%s took %.3f s  (%Rg)\n", fn[i],
                   (double) c / CLOCKS_PER_SEC, s[i]);
    }

  for (i = 0; i < n; i++)
    mpfr_clear (x[i]);
  free (x);
  free (p);
  for (i = 0; i < 3; i++)
    mpfr_clear (s[i]);
  gmp_randclear (state);
}

int main (int argc, char *argv[])
{
  int r;
  long n, nc, precx, precy, emax, ntests;
  unsigned long seed;

  if (argc != 9)
    {
      fprintf (stderr, "Usage: %s <rndmode> <size> <nc> <precx> <precs>"
               " <emax> <ntests> <seed>\n", argv[0]);
      exit (1);
    }

  r = atoi (argv[1]);
  if (r < 0 || r > 4)
    {
      fprintf (stderr, "%s: invalid rounding mode = %d\n", argv[0], r);
      exit (1);
    }

  n = atol (argv[2]);
  if (n < 0)
    {
      fprintf (stderr, "%s: invalid size n = %ld\n", argv[0], n);
      exit (1);
    }

  nc = atol (argv[3]);
  if (nc < 0 || nc >= n)
    {
      fprintf (stderr, "%s: invalid nc = %ld\n", argv[0], nc);
      exit (1);
    }

  precx = atol (argv[4]);
  if (precx < MPFR_PREC_MIN || precx > MPFR_PREC_MAX)
    {
      fprintf (stderr, "%s: invalid precx = %ld\n", argv[0], precx);
      exit (1);
    }

  precy = atol (argv[5]);
  if (precy < MPFR_PREC_MIN || precy > MPFR_PREC_MAX)
    {
      fprintf (stderr, "%s: invalid precy = %ld\n", argv[0], precy);
      exit (1);
    }

  emax = atol (argv[6]);
  if (emax < 1)
    {
      fprintf (stderr, "%s: invalid emax = %ld\n", argv[0], emax);
      exit (1);
    }

  ntests = atol (argv[7]);
  if (ntests < 1)
    {
      fprintf (stderr, "%s: invalid ntests = %ld\n", argv[0], ntests);
      exit (1);
    }

  seed = (unsigned long) atol (argv[8]);

  check_random ((mpfr_rnd_t) r, n, nc, precx, precy, emax, ntests, seed);

  return 0;
}
