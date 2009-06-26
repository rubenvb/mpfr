/* Test file for mpfr_zeta_ui.

Copyright 2005, 2006, 2007, 2008, 2009 Free Software Foundation, Inc.
Contributed by the Arenaire and Cacao projects, INRIA.

This file is part of the GNU MPFR Library.

The GNU MPFR Library is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 3 of the License, or (at your
option) any later version.

The GNU MPFR Library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
License for more details.

You should have received a copy of the GNU Lesser General Public License
along with the GNU MPFR Library; see the file COPYING.LIB.  If not, see
http://www.gnu.org/licenses/ or write to the Free Software Foundation, Inc.,
51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA. */

#include <stdio.h>
#include <stdlib.h>

#include "mpfr-test.h"

#define TEST_FUNCTION mpfr_zeta_ui

int
main (int argc, char *argv[])
{
#if MPFR_VERSION >= MPFR_VERSION_NUM(2,3,0)
  unsigned int prec, yprec;
  int rnd;
  mpfr_t x, y, z, t;
  int inexact;
  unsigned long n;

  tests_start_mpfr ();

  mpfr_init (x);
  mpfr_init (y);
  mpfr_init (z);
  mpfr_init (t);

  if (argc >= 3) /* tzeta_ui n prec [rnd] */
    {
      mpfr_set_prec (x, atoi (argv[2]));
      mpfr_zeta_ui (x, atoi (argv[1]),
                    argc > 3 ? (mpfr_rnd_t) atoi (argv[3]) : MPFR_RNDN);
      mpfr_out_str (stdout, 10, 0, x, MPFR_RNDN);
      printf ("\n");
      goto clear_and_exit;
    }

  mpfr_set_prec (x, 33);
  mpfr_set_prec (y, 33);
  mpfr_zeta_ui (x, 3, MPFR_RNDZ);
  mpfr_set_str_binary (y, "0.100110011101110100000000001001111E1");
  if (mpfr_cmp (x, y))
    {
      printf ("Error for zeta(3), prec=33, MPFR_RNDZ\n");
      printf ("expected "); mpfr_dump (y);
      printf ("got      "); mpfr_dump (x);
      exit (1);
    }

  for (prec = MPFR_PREC_MIN; prec <= 100; prec++)
    {
      mpfr_set_prec (x, prec);
      mpfr_set_prec (z, prec);
      mpfr_set_prec (t, prec);
      yprec = prec + 10;
      mpfr_set_prec (y, yprec);

      for (n = 0; n < 50; n++)
        for (rnd = 0; rnd < MPFR_RND_MAX; rnd++)
          {
            inexact = mpfr_zeta_ui (y, n, MPFR_RNDN);
            if (mpfr_can_round (y, yprec, MPFR_RNDN, MPFR_RNDZ, prec
                                + (rnd == MPFR_RNDN)))
              {
                mpfr_set (t, y, (mpfr_rnd_t) rnd);
                inexact = mpfr_zeta_ui (z, n, (mpfr_rnd_t) rnd);
                if (mpfr_cmp (t, z))
                  {
                    printf ("results differ for n=%lu", n);
                    printf (" prec=%u rnd_mode=%s\n", prec,
                            mpfr_print_rnd_mode ((mpfr_rnd_t) rnd));
                    printf ("   got      ");
                    mpfr_dump (z);
                    printf ("   expected ");
                    mpfr_dump (t);
                    printf ("   approx   ");
                    mpfr_dump (y);
                    exit (1);
                  }
              }
          }
    }

 clear_and_exit:
  mpfr_clear (x);
  mpfr_clear (y);
  mpfr_clear (z);
  mpfr_clear (t);

  tests_end_mpfr ();
#endif
  return 0;
}
