/* mpfr_div_2si -- divide a floating-point number by a power of two

Copyright 1999, 2001, 2002, 2003 Free Software Foundation, Inc.

This file is part of the MPFR Library.

The MPFR Library is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or (at your
option) any later version.

The MPFR Library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
License for more details.

You should have received a copy of the GNU Lesser General Public License
along with the MPFR Library; see the file COPYING.LIB.  If not, write to
the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
MA 02111-1307, USA. */

#include "gmp.h"
#include "gmp-impl.h"
#include "mpfr.h"
#include "mpfr-impl.h"

int
mpfr_div_2si (mpfr_ptr y, mpfr_srcptr x, long int n, mp_rnd_t rnd_mode)
{
  int inexact;

  inexact = y != x ? mpfr_set (y, x, rnd_mode) : 0;

  if (MPFR_IS_FP(y) && MPFR_NOTZERO(y))
    {
      mp_exp_t exp = MPFR_GET_EXP (y);
      if (n > 0 && (__gmpfr_emin > MPFR_EMAX_MAX - n ||
                    exp < __gmpfr_emin + n))
        {
          if (rnd_mode == GMP_RNDN &&
              (__gmpfr_emin > MPFR_EMAX_MAX - (n - 1) ||
               exp < __gmpfr_emin + (n - 1) || mpfr_powerof2_raw (y)))
            rnd_mode = GMP_RNDZ;
          return mpfr_set_underflow (y, rnd_mode, MPFR_SIGN(y));
        }

      if (n < 0 && (__gmpfr_emax < MPFR_EMIN_MIN - n ||
                    exp > __gmpfr_emax + n))
        return mpfr_set_overflow (y, rnd_mode, MPFR_SIGN(y));

      MPFR_SET_EXP (y, exp - n);
    }

  return inexact;
}
