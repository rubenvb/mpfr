/* Utilities for MPFR developers, not exported.

Copyright 1999, 2000, 2001, 2002, 2003, 2004, 2005
  Free Software Foundation, Inc.

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

#ifndef __MPFR_IMPL_H__
#define __MPFR_IMPL_H__

/* Check if we are inside a build of MPFR or inside the test suite.
   This is needed in mpfr.h to export or import the functions.
   It matters only for Windows DLL */
#ifndef __MPFR_TEST_H__
# define __MPFR_WITHIN_MPFR 1
#endif

/******************************************************
 ****************** Include files *********************
 ******************************************************/

/* Include 'config.h' before using ANY configure macros if needed
   NOTE: It isn't MPFR 'config.h', but GMP's one! */
#if defined(HAVE_CONFIG_H)
#if HAVE_CONFIG_H
#include "config.h"
#endif
#endif

#ifdef  MPFR_HAVE_GMP_IMPL /* Build with gmp internals*/

# ifndef __GMP_H__
#  include "gmp.h"
# endif
# ifndef __GMP_IMPL_H__
#  include "gmp-impl.h"
# endif
# ifdef MPFR_NEED_LONGLONG_H
#  include "longlong.h"
# endif
# ifndef __MPFR_H
#  include "mpfr.h"
# endif

#else /* Build without gmp internals */

# ifndef __GMP_H__
#  include "gmp.h"
# endif
# ifndef __MPFR_H
#  include "mpfr.h"
# endif
# ifndef __GMPFR_GMP_H__
#  include "mpfr-gmp.h"
# endif
# ifdef MPFR_NEED_LONGLONG_H
#  include "mpfr-longlong.h"
# endif

#endif
#undef MPFR_NEED_LONGLONG_H

/* Define strcasecmp and strncasecmp if needed */
#ifndef HAVE_STRCASECMP
# define strcasecmp mpfr_strcasecmp
#endif
#ifndef HAVE_STRNCASECMP
# define strncasecmp mpfr_strncasecmp
#endif


/******************************************************
 ***************** Detection macros *******************
 ******************************************************/

/* Macros to detect STDC, GCC, GLIBC, GMP and ICC version */
#if defined(__STDC_VERSION__)
# define __MPFR_STDC(version) (__STDC_VERSION__>=(version))
#elif defined(__STDC__)
# define __MPFR_STDC(version) (0 == (version))
#else
# define __MPFR_STDC(version) 0
#endif

#if defined(__GNUC__) && defined(__GNUC_MINOR__) && !defined(__ICC)
# define __MPFR_GNUC(a, i) \
 (MPFR_VERSION_NUM(__GNUC__,__GNUC_MINOR__,0)>=MPFR_VERSION_NUM(a,i,0))
#else
# define __MPFR_GNUC(a, i) 0
#endif

#if defined(__GLIBC__) && defined(__GLIBC_MINOR__)
# define __MPFR_GLIBC(a, i) \
 (MPFR_VERSION_NUM(__GLIBC__,__GLIBC_MINOR__,0)>=MPFR_VERSION_NUM(a,i,0))
#else
# define __MPFR_GLIBC(a, i) 0
#endif

#if defined(__GNU_MP_VERSION)&&defined(__GNU_MP_VERSION_MINOR)&&defined(__GNU_MP_VERSION_PATCHLEVEL)
# define __MPFR_GMP(a, b, c) \
(MPFR_VERSION_NUM(__GNU_MP_VERSION,__GNU_MP_VERSION_MINOR,__GNU_MP_VERSION_PATCHLEVEL) >= MPFR_VERSION_NUM(a,b,c))
#else
# define __MPFR_GMP(a, b, c) 0
#endif

#if defined(__ICC)
# define __MPFR_ICC(a,b,c) (__ICC >= (a)*100+(b)*10+c)
#else
# define __MPFR_ICC(a,b,c) 0
#endif



/******************************************************
 ******************** Check GMP ***********************
 ******************************************************/

#if !__MPFR_GMP(4,1,0)
# error "GMP 4.1.0 or newer needed"
#endif

#if GMP_NAIL_BITS != 0
# error "MPFR doesn't support nonzero values of GMP_NAIL_BITS"
#endif

#if (BITS_PER_MP_LIMB<32) || (BITS_PER_MP_LIMB & (BITS_PER_MP_LIMB - 1))
# error "BITS_PER_MP_LIMB must be a power of 2, and >= 32"
#endif

#if BITS_PER_MP_LIMB == 16
# define MPFR_LOG2_BITS_PER_MP_LIMB 4
#elif BITS_PER_MP_LIMB == 32
# define MPFR_LOG2_BITS_PER_MP_LIMB 5
#elif BITS_PER_MP_LIMB == 64
# define MPFR_LOG2_BITS_PER_MP_LIMB 6
#elif BITS_PER_MP_LIMB == 128
# define MPFR_LOG2_BITS_PER_MP_LIMB 7
#elif BITS_PER_MP_LIMB == 256
# define MPFR_LOG2_BITS_PER_MP_LIMB 8
#else
# error "Can't compute log2(BITS_PER_MP_LIMB)"
#endif

/* mpn_sub_nc is internal but may be defined in the header
   but not in the library! That's why we may need to overide it.*/
#ifndef MPFR_HAVE_MPN_SUB_NC
mp_limb_t mpfr_sub_nc _MPFR_PROTO ((mp_ptr, mp_srcptr, mp_srcptr, mp_size_t,
                                    mp_limb_t ));
#undef mpn_sub_nc
#define mpn_sub_nc mpfr_sub_nc
#endif


/******************************************************
 ************* Global Internal Variables **************
 ******************************************************/

#ifdef MPFR_USE_THREAD_SAFE
# if __MPFR_GNUC(3,3) || __MPFR_ICC(8,1,0)
#  define MPFR_THREAD_ATTR __thread
# else
#  error "Can't build MPFR as thread safe"
# endif
#else
# define MPFR_THREAD_ATTR
#endif

#if defined (__cplusplus)
extern "C" {
#endif

__MPFR_DECLSPEC extern MPFR_THREAD_ATTR unsigned int __gmpfr_flags;
__MPFR_DECLSPEC extern MPFR_THREAD_ATTR mp_exp_t     __gmpfr_emin;
__MPFR_DECLSPEC extern MPFR_THREAD_ATTR mp_exp_t     __gmpfr_emax;
__MPFR_DECLSPEC extern MPFR_THREAD_ATTR mp_prec_t    __gmpfr_default_fp_bit_precision;
__MPFR_DECLSPEC extern MPFR_THREAD_ATTR mpfr_rnd_t   __gmpfr_default_rounding_mode;
__MPFR_DECLSPEC extern MPFR_THREAD_ATTR mpfr_cache_t __gmpfr_cache_const_pi;
__MPFR_DECLSPEC extern MPFR_THREAD_ATTR mpfr_cache_t __gmpfr_cache_const_log2;
__MPFR_DECLSPEC extern MPFR_THREAD_ATTR mpfr_cache_t __gmpfr_cache_const_euler;
__MPFR_DECLSPEC extern MPFR_THREAD_ATTR mpfr_cache_t __gmpfr_cache_const_catalan;

#if defined (__cplusplus)
 }
#endif

/* Flags of __gmpfr_flags */
#define MPFR_FLAGS_UNDERFLOW 1
#define MPFR_FLAGS_OVERFLOW 2
#define MPFR_FLAGS_NAN 4
#define MPFR_FLAGS_INEXACT 8
#define MPFR_FLAGS_ERANGE 16
#define MPFR_FLAGS_ALL 31

/* Replace some commun functions for direct access to the global vars */
#define mpfr_get_emin() (__gmpfr_emin + 0)
#define mpfr_get_emax() (__gmpfr_emax + 0)
#define mpfr_get_default_rounding_mode() (__gmpfr_default_rounding_mode + 0)
#define mpfr_get_default_prec() (__gmpfr_default_fp_bit_precision + 0)

#define mpfr_clear_flags() \
  ((void) (__gmpfr_flags = 0))
#define mpfr_clear_underflow() \
  ((void) (__gmpfr_flags &= MPFR_FLAGS_ALL ^ MPFR_FLAGS_UNDERFLOW))
#define mpfr_clear_overflow() \
  ((void) (__gmpfr_flags &= MPFR_FLAGS_ALL ^ MPFR_FLAGS_OVERFLOW))
#define mpfr_clear_nanflag() \
  ((void) (__gmpfr_flags &= MPFR_FLAGS_ALL ^ MPFR_FLAGS_NAN))
#define mpfr_clear_inexflag() \
  ((void) (__gmpfr_flags &= MPFR_FLAGS_ALL ^ MPFR_FLAGS_INEXACT))
#define mpfr_clear_erangeflag() \
  ((void) (__gmpfr_flags &= MPFR_FLAGS_ALL ^ MPFR_FLAGS_ERANGE))
#define mpfr_underflow_p() \
  ((int) (__gmpfr_flags & MPFR_FLAGS_UNDERFLOW))
#define mpfr_overflow_p() \
  ((int) (__gmpfr_flags & MPFR_FLAGS_OVERFLOW))
#define mpfr_nanflag_p() \
  ((int) (__gmpfr_flags & MPFR_FLAGS_NAN))
#define mpfr_inexflag_p() \
  ((int) (__gmpfr_flags & MPFR_FLAGS_INEXACT))
#define mpfr_erangeflag_p() \
  ((int) (__gmpfr_flags & MPFR_FLAGS_ERANGE))
 

/******************************************************
 ******************** Assertions **********************
 ******************************************************/

/* Compile with -DWANT_ASSERT to check all assert statements */

/* Note: do not use GMP macros ASSERT_ALWAYS and ASSERT as they are not
   expressions, and as a consequence, they cannot be used in a for(),
   with a comma operator and so on. */

/* MPFR_ASSERTN(expr): assertions that should always be checked */
#define MPFR_ASSERTN(expr)  \
   ((void) ((MPFR_UNLIKELY(expr)) || MPFR_UNLIKELY( (ASSERT_FAIL(expr),0) )))

/* MPFR_ASSERTD(expr): assertions that should be checked when testing */
#ifdef WANT_ASSERT
# define MPFR_EXP_CHECK 1
# define MPFR_ASSERTD(expr)  MPFR_ASSERTN (expr)
#else
# define MPFR_ASSERTD(expr)  ((void) 0)
#endif

/* Check if the args are correct  */
/* Can't be used since TMP variables are not correct */
#define MPFR_CHECK1(x,r) \
 MPFR_ASSERTD(mpfr_check(x) && GMP_RNDN <= r && r <= GMP_RNDD)
#define MPFR_CHECK2(x,y,r) \
 MPFR_ASSERTD(mpfr_check(x) && mpfr_check(y) && GMP_RNDN <= r && r <= GMP_RNDD)
#define MPFR_CHECK3(x,y,z,r) \
 MPFR_ASSERTD(mpfr_check(x) && mpfr_check(y) && mpfr_check(z) && \
  GMP_RNDN <= r && r <= GMP_RNDD)

/* Code to deal with impossible
   WARNING: It doesn't use do { } while (0) for Insure++*/
#define MPFR_RET_NEVER_GO_HERE()  {MPFR_ASSERTN(0); return 0;}



/******************************************************
 ****************** double macros *********************
 ******************************************************/

/* Definition of constants */
#define LOG2 0.69314718055994528622 /* log(2) rounded to zero on 53 bits */
#define ALPHA 4.3191365662914471407 /* a+2 = a*log(a), rounded to +infinity */

/* Debug non IEEE floats */
#ifdef XDEBUG
# undef _GMP_IEEE_FLOATS
#endif
#ifndef _GMP_IEEE_FLOATS
# define _GMP_IEEE_FLOATS 0
#endif

#ifndef IEEE_DBL_MANT_DIG
#define IEEE_DBL_MANT_DIG 53
#endif
#define MPFR_LIMBS_PER_DOUBLE ((IEEE_DBL_MANT_DIG-1)/BITS_PER_MP_LIMB+1)

/* Visual C++ doesn't support +1.0/.00, -1.0/0.0 and 0.0/0.0
   at compile time. */
#if defined(_MSC_VER) && defined(_WIN32) && (_MSC_VER >= 1200)
static double double_zero = 0.0;
# define DBL_NAN (double_zero/double_zero)
# define DBL_POS_INF ((double) 1.0/double_zero)
# define DBL_NEG_INF ((double)-1.0/double_zero)
#else
# define DBL_POS_INF ((double) 1.0/0.0)
# define DBL_NEG_INF ((double)-1.0/0.0)
# define DBL_NAN     ((double) 0.0/0.0)
#endif

/* for x of type ieee_double_extract */
#if _GMP_IEEE_FLOATS
typedef union ieee_double_extract Ieee_double_extract;

# define DOUBLE_ISNANorINF(x) (((Ieee_double_extract *)&(x))->s.exp == 0x7ff)
# define DOUBLE_ISINF(x) (DOUBLE_ISNANorINF(x) && \
			 (((Ieee_double_extract *)&(x))->s.manl == 0) && \
                         (((Ieee_double_extract *)&(x))->s.manh == 0))
# define DOUBLE_ISNAN(x) (DOUBLE_ISNANorINF(x) && \
			 ((((Ieee_double_extract *)&(x))->s.manl != 0) || \
                         (((Ieee_double_extract *)&(x))->s.manh != 0)))
#else
# define DOUBLE_ISINF(x) ((x) > DBL_MAX || (x) < -DBL_MAX)
# define DOUBLE_ISNAN(x) ((x) != (x))
#endif



/******************************************************
 *************** Long double macros *******************
 ******************************************************/

/* we only require that LDBL_MANT_DIG is a bound on the mantissa length
   of the "long double" type */
#define MPFR_LDBL_MANT_DIG   \
  (sizeof(long double)*BITS_PER_MP_LIMB/sizeof(mp_limb_t))
#define MPFR_LIMBS_PER_LONG_DOUBLE \
  ((sizeof(long double)-1)/sizeof(mp_limb_t)+1)

/* LONGDOUBLE_NAN_ACTION executes the code "action" if x is a NaN. */

/* On hppa2.0n-hp-hpux10 with the unbundled HP cc, the test x!=x on a NaN
   has been seen false, meaning NaNs are not detected.  This seemed to
   happen only after other comparisons, not sure what's really going on.  In
   any case we can pick apart the bytes to identify a NaN.  */
#ifdef HAVE_LDOUBLE_IEEE_QUAD_BIG
# define LONGDOUBLE_NAN_ACTION(x, action)                        \
  do {                                                          \
    union {                                                     \
      long double    ld;                                        \
      struct {                                                  \
        unsigned long  sign : 1;                                \
        unsigned long  exp  : 15;                               \
        unsigned long  man3 : 16;                               \
        unsigned long  man2 : 32;                               \
        unsigned long  man1 : 32;                               \
        unsigned long  man0 : 32;                               \
      } s;                                                      \
    } u;                                                        \
    u.ld = (x);                                                 \
    if (u.s.exp == 0x7FFFL                                      \
        && (u.s.man0 | u.s.man1 | u.s.man2 | u.s.man3) != 0)    \
      { action; }                                               \
  } while (0)
#endif

/* Under IEEE rules, NaN is not equal to anything, including itself.
   "volatile" here stops "cc" on mips64-sgi-irix6.5 from optimizing away
   x!=x. */
#ifndef LONGDOUBLE_NAN_ACTION
# define LONGDOUBLE_NAN_ACTION(x, action)                \
  do {                                                  \
    volatile long double __x = LONGDOUBLE_VOLATILE (x); \
    if ((x) != __x)                                     \
      { action; }                                       \
  } while (0)
# define WANT_LONGDOUBLE_VOLATILE 1
#endif

/* If we don't have a proper "volatile" then volatile is #defined to empty,
   in this case call through an external function to stop the compiler
   optimizing anything. */
#ifdef WANT_LONGDOUBLE_VOLATILE
# ifdef volatile
__MPFR_DECLSPEC long double __gmpfr_longdouble_volatile _MPFR_PROTO ((long double)) ATTRIBUTE_CONST;
#  define LONGDOUBLE_VOLATILE(x)  (__gmpfr_longdouble_volatile (x))
#  define WANT_GMPFR_LONGDOUBLE_VOLATILE 1
# else
#  define LONGDOUBLE_VOLATILE(x)  (x)
# endif
#endif

/* Some special case for IEEE_EXT Litle Endian */
#if HAVE_LDOUBLE_IEEE_EXT_LITTLE

typedef union {
  long double    ld;
  struct {
    unsigned long manl : 32;
    unsigned long manh : 32;
    unsigned long expl : 8 ;
    unsigned long exph : 7;
    unsigned long sign : 1;
  } s;
} mpfr_long_double_t;

#undef MPFR_LDBL_MANT_DIG
#undef MPFR_LIMBS_PER_LONG_DOUBLE
#define MPFR_LDBL_MANT_DIG   64
#define MPFR_LIMBS_PER_LONG_DOUBLE ((64-1)/BITS_PER_MP_LIMB+1)

#endif

/******************************************************
 **************** mpfr_t properties *******************
 ******************************************************/

#define MPFR_PREC(x)      ((x)->_mpfr_prec)
#define MPFR_EXP(x)       ((x)->_mpfr_exp)
#define MPFR_MANT(x)      ((x)->_mpfr_d)
#define MPFR_LIMB_SIZE(x) ((MPFR_PREC((x))-1)/BITS_PER_MP_LIMB+1)

#if   _MPFR_PREC_FORMAT == 1
# define MPFR_INTPREC_MAX (USHRT_MAX & ~(unsigned int) (BITS_PER_MP_LIMB - 1))
#elif _MPFR_PREC_FORMAT == 2
# define MPFR_INTPREC_MAX (UINT_MAX & ~(unsigned int) (BITS_PER_MP_LIMB - 1))
#elif _MPFR_PREC_FORMAT == 3
# define MPFR_INTPREC_MAX (ULONG_MAX & ~(unsigned long) (BITS_PER_MP_LIMB - 1))
#else
# error "Invalid MPFR Prec format"
#endif



/******************************************************
 ***************** exponent limits ********************
 ******************************************************/

/* Defined limits and unsigned type of exponent */
#if __GMP_MP_SIZE_T_INT == 1
typedef unsigned int            mpfr_uexp_t;
# define MPFR_EXP_MAX (INT_MAX)
# define MPFR_EXP_MIN (INT_MIN)
#else
typedef unsigned long int  mpfr_uexp_t;
# define MPFR_EXP_MAX (LONG_MAX)
# define MPFR_EXP_MIN (LONG_MIN)
#endif
#ifndef mp_exp_unsigned_t
# define mp_exp_unsigned_t mpfr_uexp_t
#endif

/* Invalid exponent value (to track bugs...) */
#define MPFR_EXP_INVALID \
 ((mp_exp_t) 1 << (BITS_PER_MP_LIMB*sizeof(mp_exp_t)/sizeof(mp_limb_t)-2))

/* Definition of the intervals of the exponent limits */
#undef MPFR_EMIN_MIN
#undef MPFR_EMIN_MAX
#undef MPFR_EMAX_MIN
#undef MPFR_EMAX_MAX
#define MPFR_EMIN_MIN (1-MPFR_EXP_INVALID)
#define MPFR_EMIN_MAX (MPFR_EXP_INVALID-1)
#define MPFR_EMAX_MIN (1-MPFR_EXP_INVALID)
#define MPFR_EMAX_MAX (MPFR_EXP_INVALID-1)

/* Use MPFR_GET_EXP and MPFR_SET_EXP instead of MPFR_EXP directly,
   unless when the exponent may be out-of-range, for instance when
   setting the exponent before calling mpfr_check_range.
   MPFR_EXP_CHECK is defined when WANT_ASSERT is defined, but if you
   don't use WANT_ASSERT (for speed reasons), you can still define
   MPFR_EXP_CHECK by setting -DMPFR_EXP_CHECK in $CFLAGS. */

#ifdef MPFR_EXP_CHECK
# define MPFR_GET_EXP(x)          mpfr_get_exp (x)
# define MPFR_SET_EXP(x, exp)     MPFR_ASSERTN (!mpfr_set_exp ((x), (exp)))
# define MPFR_SET_INVALID_EXP(x)  ((void) (MPFR_EXP (x) = MPFR_EXP_INVALID))
#else
# define MPFR_GET_EXP(x)          MPFR_EXP (x)
# define MPFR_SET_EXP(x, exp)     ((void) (MPFR_EXP (x) = (exp)))
# define MPFR_SET_INVALID_EXP(x)  ((void) 0)
#endif



/******************************************************
 ********** Singular Values (NAN, INF, ZERO) **********
 ******************************************************/

/*
 * Clear flags macros are still defined and should be still used
 * since the functions must not assume the internal format.
 * How to deal with special values ?
 *  1. Check if is a special value (Zero, Nan, Inf) wiht MPFR_IS_SINGULAR
 *  2. Deal with the special value with MPFR_IS_NAN, MPFR_IS_INF, etc
 *  3. Else clear the flags of the dest (it must be done after since src
 *     may be also the dest!)
 * MPFR_SET_INF, MPFR_SET_NAN, MPFR_SET_ZERO must clear by
 * themselves the other flags.
 */

/* Enum special value of exponent.*/
# define MPFR_EXP_ZERO (MPFR_EXP_MIN+1)
# define MPFR_EXP_NAN  (MPFR_EXP_MIN+2)
# define MPFR_EXP_INF  (MPFR_EXP_MIN+3)

#define MPFR_CLEAR_FLAGS(x)

#define MPFR_IS_NAN(x)   (MPFR_EXP(x) == MPFR_EXP_NAN)
#define MPFR_SET_NAN(x)  (MPFR_EXP(x) =  MPFR_EXP_NAN)
#define MPFR_IS_INF(x)   (MPFR_EXP(x) == MPFR_EXP_INF)
#define MPFR_SET_INF(x)  (MPFR_EXP(x) =  MPFR_EXP_INF)
#define MPFR_IS_ZERO(x)  (MPFR_EXP(x) == MPFR_EXP_ZERO)
#define MPFR_SET_ZERO(x) (MPFR_EXP(x) =  MPFR_EXP_ZERO)
#define MPFR_NOTZERO(x)  (MPFR_EXP(x) != MPFR_EXP_ZERO)

#define MPFR_IS_FP(x)       (!MPFR_IS_NAN(x) && !MPFR_IS_INF(x))
#define MPFR_IS_SINGULAR(x) (MPFR_EXP(x) <= MPFR_EXP_INF)
#define MPFR_IS_PURE_FP(x)  (!MPFR_IS_SINGULAR(x))

#define MPFR_ARE_SINGULAR(x,y) \
  (MPFR_UNLIKELY(MPFR_IS_SINGULAR(x)) || MPFR_UNLIKELY(MPFR_IS_SINGULAR(y)))



/******************************************************
 ********************* Sign Macros ********************
 ******************************************************/

#define MPFR_SIGN_POS (1)
#define MPFR_SIGN_NEG (-1)

#define MPFR_IS_STRICTPOS(x)  (MPFR_NOTZERO((x)) && MPFR_SIGN(x) > 0)
#define MPFR_IS_STRICTNEG(x)  (MPFR_NOTZERO((x)) && MPFR_SIGN(x) < 0)

#define MPFR_IS_NEG(x) (MPFR_SIGN(x) < 0)
#define MPFR_IS_POS(x) (MPFR_SIGN(x) > 0)

#define MPFR_SET_POS(x) (MPFR_SIGN(x) = MPFR_SIGN_POS)
#define MPFR_SET_NEG(x) (MPFR_SIGN(x) = MPFR_SIGN_NEG)

#define MPFR_CHANGE_SIGN(x) (MPFR_SIGN(x) = -MPFR_SIGN(x))
#define MPFR_SET_SAME_SIGN(x, y) (MPFR_SIGN(x) = MPFR_SIGN(y))
#define MPFR_SET_OPPOSITE_SIGN(x, y) (MPFR_SIGN(x) = -MPFR_SIGN(y))
#define MPFR_ASSERT_SIGN(s) \
 (MPFR_ASSERTD((s) == MPFR_SIGN_POS || (s) == MPFR_SIGN_NEG))
#define MPFR_SET_SIGN(x, s) \
  (MPFR_ASSERT_SIGN(s), MPFR_SIGN(x) = s)
#define MPFR_IS_POS_SIGN(s1) (s1 > 0)
#define MPFR_IS_NEG_SIGN(s1) (s1 < 0)
#define MPFR_MULT_SIGN(s1, s2) ((s1) * (s2))
/* Transform a sign to 1 or -1 */
#define MPFR_FROM_SIGN_TO_INT(s) (s)
#define MPFR_INT_SIGN(x) MPFR_FROM_SIGN_TO_INT(MPFR_SIGN(x))



/******************************************************
 ***************** Ternary Value Macros ***************
 ******************************************************/

/* Special inexact value */
#define MPFR_EVEN_INEX 2

/* When returning the ternary inexact value, ALWAYS use one of the
   following two macros, unless the flag comes from another function
   returning the ternary inexact value */
#define MPFR_RET(I) return \
  (I) ? ((__gmpfr_flags |= MPFR_FLAGS_INEXACT), (I)) : 0
#define MPFR_RET_NAN return (__gmpfr_flags |= MPFR_FLAGS_NAN), 0

#define MPFR_SET_ERANGE() (__gmpfr_flags |= MPFR_FLAGS_ERANGE)



/******************************************************
 ************** Rounding mode macros  *****************
 ******************************************************/

/* We want to test this :
 *  (rnd == GMP_RNDU && test) || (rnd == RNDD && !test)
 * ie it transforms RNDU or RNDD to Away or Zero according to the sign */
#define MPFR_IS_RNDUTEST_OR_RNDDNOTTEST(rnd, test) \
  (((rnd) + (test)) == GMP_RNDD)

/* We want to test if rnd = Zero, or Away.
   'test' is true iff negative. */
#define MPFR_IS_LIKE_RNDZ(rnd, test) \
  ((rnd==GMP_RNDZ) || MPFR_IS_RNDUTEST_OR_RNDDNOTTEST (rnd, test))

/* Invert a rounding mode */
#define MPFR_INVERT_RND(rnd) ((rnd == GMP_RNDU) ? GMP_RNDD : \
                             ((rnd == GMP_RNDD) ? GMP_RNDU : rnd))

/* Transform RNDU and RNDD to RNDA or RNDZ */
#define MPFR_UPDATE_RND_MODE(rnd, test)                            \
  do {                                                             \
    if (MPFR_UNLIKELY(MPFR_IS_RNDUTEST_OR_RNDDNOTTEST(rnd, test))) \
      rnd = GMP_RNDZ;                                              \
  } while (0)



/******************************************************
 ******************* Limb Macros **********************
 ******************************************************/

 /* Definition of MPFR_LIMB_HIGHBIT */
#if defined(GMP_LIMB_HIGHBIT)
# define MPFR_LIMB_HIGHBIT GMP_LIMB_HIGHBIT
#elif defined(MP_LIMB_T_HIGHBIT)
# define MPFR_LIMB_HIGHBIT MP_LIMB_T_HIGHBIT
#else
# error "Neither GMP_LIMB_HIGHBIT nor MP_LIMB_T_HIGHBIT defined in GMP"
#endif

/* Mask to get the Most Significent Bit of a limb */
#define MPFR_LIMB_MSB(l) ((l)&MPFR_LIMB_HIGHBIT)

/* Definition of MPFR_LIMB_ONE & MPFR_LIMB_ZERO*/
#ifdef CNST_LIMB
# define MPFR_LIMB_ONE  CNST_LIMB(1)
# define MPFR_LIMB_ZERO CNST_LIMB(0)
#else
# define MPFR_LIMB_ONE  ((mp_limb_t) 1L)
# define MPFR_LIMB_ZERO ((mp_limb_t) 0L)
#endif

/* Mask for the low 's' bits of a limb */
#define MPFR_LIMB_MASK(s) ((MPFR_LIMB_ONE<<(s))-MPFR_LIMB_ONE)



/******************************************************
 ********************** Memory ************************
 ******************************************************/

/* Heap Memory gestion */
typedef union { mp_size_t s; mp_limb_t l; } mpfr_size_limb_t;
#define MPFR_GET_ALLOC_SIZE(x) \
 ( ((mp_size_t*) MPFR_MANT(x))[-1] + 0)
#define MPFR_SET_ALLOC_SIZE(x, n) \
 ( ((mp_size_t*) MPFR_MANT(x))[-1] = n)
#define MPFR_MALLOC_SIZE(s) \
  ( sizeof(mpfr_size_limb_t) + BYTES_PER_MP_LIMB * ((size_t) s) )
#define MPFR_SET_MANT_PTR(x,p) \
   (MPFR_MANT(x) = (mp_limb_t*) ((mpfr_size_limb_t*) p + 1))
#define MPFR_GET_REAL_PTR(x) \
   ((mp_limb_t*) ((mpfr_size_limb_t*) MPFR_MANT(x) - 1))

/* Temporary memory gestion */
/* This code is experimental: don't use it */
#ifdef MPFR_USE_OWN_TMP_ALLOC
extern unsigned char *mpfr_stack;
#undef TMP_DECL
#undef TMP_MARK
#undef TMP_ALLOC
#undef TMP_FREE
#define TMP_DECL(_x) unsigned char *(_x)
#define TMP_MARK(_x) ((_x) = mpfr_stack)
#define TMP_ALLOC(_s) (mpfr_stack += (_s), mpfr_stack - (_s))
#define TMP_FREE(_x) (mpfr_stack = (_x))
#endif

/* temporary allocate 1 limb at xp, and initialize mpfr variable x */
/* The temporary var doesn't have any size field, but it doesn't matter
 * since only functions dealing with the Heap care about it */
#define MPFR_TMP_INIT1(xp, x, p) \
 ( MPFR_PREC(x) = (p), \
   MPFR_MANT(x) = (xp), \
   MPFR_SET_POS(x), \
   MPFR_SET_INVALID_EXP(x))

#define MPFR_TMP_INIT(xp, x, p, s) \
  (xp = (mp_ptr) TMP_ALLOC(BYTES_PER_MP_LIMB * ((size_t) s)), \
   MPFR_TMP_INIT1(xp, x, p))

#define MPFR_TMP_INIT_ABS(d, s) \
 ( MPFR_PREC(d) = MPFR_PREC(s), \
   MPFR_MANT(d) = MPFR_MANT(s), \
   MPFR_SET_POS(d), \
   MPFR_EXP(d)  = MPFR_EXP(s))



/******************************************************
 *****************  Cache macros **********************
 ******************************************************/

#define mpfr_const_pi(_d,_r)    mpfr_cache(_d, __gmpfr_cache_const_pi,_r)
#define mpfr_const_log2(_d,_r)  mpfr_cache(_d, __gmpfr_cache_const_log2, _r)
#define mpfr_const_euler(_d,_r) mpfr_cache(_d, __gmpfr_cache_const_euler, _r)
#define mpfr_const_catalan(_d,_r) mpfr_cache(_d,__gmpfr_cache_const_catalan,_r)

#define MPFR_DECL_INIT_CACHE(_cache,_func) \
 mpfr_cache_t MPFR_THREAD_ATTR _cache = \
    {{{{0,MPFR_SIGN_POS,0,(mp_limb_t*)0}},0,_func}}



/******************************************************
 *******************  Threshold ***********************
 ******************************************************/

#include "mparam.h"

/******************************************************
 *****************  Useful macros *********************
 ******************************************************/

/* Theses macros help the compiler to determine if a test is
 * likely or unlikely. */
#if __MPFR_GNUC(3,0) || __MPFR_ICC(8,1,0)
# define MPFR_LIKELY(x) (__builtin_expect(!!(x),1))
# define MPFR_UNLIKELY(x) (__builtin_expect((x),0))
#else
# define MPFR_LIKELY(x) (x)
# define MPFR_UNLIKELY(x) (x)
#endif

/* Ceil log 2: If GCC, uses a GCC extension, otherwise calls a function */
/* Warning:
 *   Needs to define MPFR_NEED_LONGLONG.
 *   Computes ceil(log2(x)) only for x integer (unsigned long)
 *   Undefined if x is 0 */
#if __MPFR_GNUC(2,95) || __MPFR_ICC(8,1,0)
# define MPFR_INT_CEIL_LOG2(x)                            \
    (__extension__ ({int _b; mp_limb_t _limb = (x);       \
      MPFR_ASSERTD (_limb == (x));                        \
      count_leading_zeros (_b, _limb);                    \
      (BITS_PER_MP_LIMB - _b); }))
#else
# define MPFR_INT_CEIL_LOG2(x) (__gmpfr_int_ceil_log2(x))
#endif

/* Add two integers with overflow handling */
/* Example: MPFR_SADD_OVERFLOW (c, a, b, long, unsigned long,
 *                              LONG_MIN, LONG_MAX,
 * 	                        goto overflow, goto underflow); */
#define MPFR_UADD_OVERFLOW(c,a,b,ACTION_IF_OVERFLOW) \
 do { \
  (c) = (a) + (b); \
  if ((c) < (a)) ACTION_IF_OVERFLOW; \
 } while (0)

#define MPFR_SADD_OVERFLOW(c,a,b,STYPE,UTYPE,MIN,MAX,ACTION_IF_POS_OVERFLOW,ACTION_IF_NEG_OVERFLOW) \
  do { \
  if ((a) >= 0 && (b) >= 0) { \
         UTYPE uc,ua,ub; \
         ua = (UTYPE) a; ub = (UTYPE) b; \
         MPFR_UADD_OVERFLOW (uc, ua, ub, ACTION_IF_POS_OVERFLOW); \
         if (uc > (UTYPE)(MAX)) ACTION_IF_POS_OVERFLOW; \
         else (c) = (STYPE) uc; \
  } else if ((a) < 0 && (b) < 0) { \
         UTYPE uc,ua,ub; \
         ua = -(UTYPE) a; ub = -(UTYPE) b; \
         MPFR_UADD_OVERFLOW (uc, ua, ub, ACTION_IF_NEG_OVERFLOW); \
         if (uc >= -(UTYPE)(MIN) || uc > (UTYPE)(MAX)) { \
           if (uc ==  -(UTYPE)(MIN)) (c) = (MIN); \
           else  ACTION_IF_NEG_OVERFLOW; } \
         else (c) = -(STYPE) uc; \
  } else (c) = (a) + (b); \
 } while (0)


/* Set a number to 1 (Fast) */
#define MPFR_SET_ONE(x) \
do { \
  mp_size_t s = MPFR_LIMB_SIZE(x) - 1;\
  MPFR_SET_POS(x);\
  MPFR_EXP(x) = 1;\
  MPN_ZERO ( MPFR_MANT(x), s);\
  MPFR_MANT(x)[s] = MPFR_LIMB_HIGHBIT;\
} while (0)

/* Compute s = (-a) % BITS_PER_MP_LIMB
 * a is unsigned! Check if it works,
 * otherwise tries another way to compute it */
#define MPFR_UNSIGNED_MINUS_MODULO(s, a)                          \
  do                                                              \
    {                                                             \
      if ((UINT_MAX % BITS_PER_MP_LIMB) == (BITS_PER_MP_LIMB-1))  \
        (s) = (-(a)) % BITS_PER_MP_LIMB;                          \
      else                                                        \
        {                                                         \
          (s) = (a) % BITS_PER_MP_LIMB;                           \
          if (s != 0)                                             \
            (s) = BITS_PER_MP_LIMB - (s);                         \
        }                                                         \
      MPFR_ASSERTD ((s) >= 0 && (s) < BITS_PER_MP_LIMB);          \
    }                                                             \
  while (0)

/* Use it only for debug reasons */
/*   MPFR_TRACE (operation) : execute operation iff DEBUG flag is set */
/*   MPFR_DUMP (x) : print x (a mpfr_t) on stdout */
#ifdef DEBUG
# include <stdio.h>
# define MPFR_TRACE(x) x
#else
# define MPFR_TRACE(x) (void) 0
#endif
#define MPFR_DUMP(x) ( printf(#x"="), mpfr_dump(x) )

/* Test if X (positive) is a power of 2 */
#define IS_POW2(X) (((X) & ((X) - 1)) == 0)
#define NOT_POW2(X) (((X) & ((X) - 1)) != 0)

/* Safe absolute value (to avoid possible integer overflow) */
/* type is the target (unsigned) type */
#define SAFE_ABS(type,x) ((x) >= 0 ? (type)(x) : -(type)(x))

#define mpfr_get_d1(x) mpfr_get_d(x,__gmpfr_default_rounding_mode)

#define MPFR_MPZ_SIZEINBASE2(r, z)              \
  do {                                          \
   int _cnt;                                    \
   mp_size_t _size;                             \
   MPFR_ASSERTD (mpz_sgn (z) != 0);             \
   _size = ABSIZ(z);                            \
   count_leading_zeros (_cnt, PTR(z)[_size-1]); \
   (r) = _size * BITS_PER_MP_LIMB - _cnt;       \
  } while (0)

/******************************************************
 **************  Save exponent macros  ****************
 ******************************************************/

/* See README.dev for details on how to use the macros.
   They are used to make the exponent range to be maximal
   temporarily */

typedef struct {
  unsigned int saved_flags;
  mp_exp_t saved_emin;
  mp_exp_t saved_emax;
} mpfr_save_expo_t;

#define MPFR_SAVE_EXPO_DECL(x) mpfr_save_expo_t x
#define MPFR_SAVE_EXPO_MARK(x)     \
 ((x).saved_flags = __gmpfr_flags, \
  (x).saved_emin = __gmpfr_emin,   \
  (x).saved_emax = __gmpfr_emax,   \
  __gmpfr_emin = MPFR_EMIN_MIN,    \
  __gmpfr_emax = MPFR_EMAX_MAX)
#define MPFR_SAVE_EXPO_FREE(x)     \
 (__gmpfr_flags = (x).saved_flags, \
  __gmpfr_emin = (x).saved_emin,   \
  __gmpfr_emax = (x).saved_emax)

/* Speed up final checking */
#define mpfr_check_range(x,t,r) \
 (MPFR_LIKELY (MPFR_EXP (x) >= __gmpfr_emin && MPFR_EXP (x) <= __gmpfr_emax) \
               ? (t) : mpfr_check_range(x,t,r))


/******************************************************
 *****************  Inline Rounding *******************
 ******************************************************/

/*
 * Round Mantissa (`srcp`, `sprec`) to mpfr_t `dest` using rounding mode `rnd`
 * assuming dest's sign is `sign`.
 * Execute OVERFLOW_HANDLER in case of overflow when rounding (Power 2 case)
 */
#define MPFR_RNDRAW(inexact, dest, srcp, sprec, rnd, sign, OVERFLOW_HANDLER)\
  do {                                                                      \
    mp_size_t dests, srcs;                                                  \
    mp_limb_t *destp;                                                       \
    mp_prec_t destprec, srcprec;                                            \
                                                                            \
    /* Check Trivial Case when Dest Mantissa has more bits than source */   \
    srcprec = sprec;                                                        \
    destprec = MPFR_PREC (dest);                                            \
    destp = MPFR_MANT (dest);                                               \
    if (MPFR_UNLIKELY (destprec >= srcprec))                                \
      {                                                                     \
	srcs  = (srcprec  + BITS_PER_MP_LIMB-1)/BITS_PER_MP_LIMB;           \
	dests = (destprec + BITS_PER_MP_LIMB-1)/BITS_PER_MP_LIMB - srcs;    \
	MPN_COPY (destp + dests, srcp, srcs);                               \
	MPN_ZERO (destp, dests);                                            \
	inexact = 0;                                                        \
      }                                                                     \
    else                                                                    \
      {                                                                     \
	/* Non trivial case: rounding needed */                             \
	mp_prec_t sh;                                                       \
	mp_limb_t *sp;                                                      \
	mp_limb_t rb, sb, ulp;                                              \
	                                                                    \
	/* Compute Position and shift */                                    \
	srcs  = (srcprec  + BITS_PER_MP_LIMB-1)/BITS_PER_MP_LIMB;           \
	dests = (destprec + BITS_PER_MP_LIMB-1)/BITS_PER_MP_LIMB;           \
	MPFR_UNSIGNED_MINUS_MODULO (sh, destprec);                          \
	sp = srcp + srcs - dests;                                           \
	                                                                    \
	/* General case when prec % BITS_PER_MP_LIMB != 0 */                \
	if (MPFR_LIKELY (sh != 0))                                          \
	  {                                                                 \
	    mp_limb_t mask;                                                 \
	    /* Compute Rounding Bit and Sticky Bit */                       \
	    mask = MPFR_LIMB_ONE << (sh-1);                                 \
	    rb = sp[0] & mask;                                              \
	    sb = sp[0] & (mask-1);                                          \
	    if (MPFR_UNLIKELY (sb == 0))                                    \
	      { /* TODO: Improve it */                                      \
		mp_limb_t *tmp;                                             \
		mp_size_t n;                                                \
		for (tmp = sp, n = srcs - dests ; n != 0 && sb == 0 ; n--)  \
		  sb = *--tmp;                                              \
	      }                                                             \
	    ulp = 2*mask;                                                   \
	  }                                                                 \
	else /* sh == 0 */                                                  \
	  {                                                                 \
	    MPFR_ASSERTD (dests < srcs);                                    \
	    /* Compute Rounding Bit and Sticky Bit */                       \
	    rb = sp[-1] & MPFR_LIMB_HIGHBIT;                                \
	    sb = sp[-1] & (MPFR_LIMB_HIGHBIT-1);                            \
	    if (MPFR_UNLIKELY (sb == 0))                                    \
	      {                                                             \
		mp_limb_t *tmp;                                             \
		mp_size_t n;                                                \
		for (tmp = sp-1, n = srcs - dests-1 ; n!=0 && sb==0 ; n--)  \
		  sb = *--tmp;                                              \
	      }                                                             \
	    ulp = MPFR_LIMB_ONE;                                            \
	  }                                                                 \
	/* Rounding */                                                      \
	if (MPFR_LIKELY (rnd == GMP_RNDN))                                  \
	  {                                                                 \
	    if (rb == 0 || MPFR_UNLIKELY (sb == 0 && (sp[0] & ulp) == 0))   \
	      {                                                             \
	      trunc:                                                        \
		inexact = MPFR_LIKELY ((sb | rb) != 0) ? -sign : 0;         \
		MPN_COPY (destp, sp, dests);                                \
		destp[0] &= ~(ulp-1);                                       \
	      }                                                             \
	    else                                                            \
              {                                                             \
	      addoneulp:                                                    \
		if (MPFR_UNLIKELY (mpn_add_1 (destp, sp, dests, ulp)))      \
		  {                                                         \
		    destp[dests-1] = MPFR_LIMB_HIGHBIT;                     \
		    OVERFLOW_HANDLER;                                       \
		  }                                                         \
		destp[0] &= ~(ulp-1);                                       \
                inexact = sign;                                             \
	      }                                                             \
	  }                                                                 \
	else                                                                \
	  { /* Not Rounding to Nearest */                                   \
	    if (MPFR_LIKELY (MPFR_IS_LIKE_RNDZ (rnd, MPFR_IS_NEG_SIGN (sign)))\
		|| MPFR_UNLIKELY ((sb | rb) == 0))                          \
	      goto trunc;                                                   \
	     else                                                           \
	      goto addoneulp;                                               \
	  }                                                                 \
      }                                                                     \
  } while (0)

/*
 * Round Mantissa (`srcp`, `sprec`) to mpfr_t `dest` using rounding mode `rnd`
 * assuming dest's sign is `sign`.
 * Execute OVERFLOW_HANDLE in case of overflow when rounding (Power 2 case)
 * Return MPFR_EVEN_INEX in case of EVEN rounding
 */
#define MPFR_RNDRAW_EVEN(inexact, dest, srcp, sprec, rnd, sign, OVERFLOW_HANDLER)\
  do {                                                                      \
    mp_size_t dests, srcs;                                                  \
    mp_limb_t *destp;                                                       \
    mp_prec_t destprec, srcprec;                                            \
                                                                            \
    /* Check Trivial Case when Dest Mantissa has more bits than source */   \
    srcprec = sprec;                                                        \
    destprec = MPFR_PREC (dest);                                            \
    destp = MPFR_MANT (dest);                                               \
    if (MPFR_UNLIKELY (destprec >= srcprec))                                \
      {                                                                     \
	srcs  = (srcprec  + BITS_PER_MP_LIMB-1)/BITS_PER_MP_LIMB;           \
	dests = (destprec + BITS_PER_MP_LIMB-1)/BITS_PER_MP_LIMB - srcs;    \
	MPN_COPY (destp + dests, srcp, srcs);                               \
	MPN_ZERO (destp, dests);                                            \
	inexact = 0;                                                        \
      }                                                                     \
    else                                                                    \
      {                                                                     \
	/* Non trivial case: rounding needed */                             \
	mp_prec_t sh;                                                       \
	mp_limb_t *sp;                                                      \
	mp_limb_t rb, sb, ulp;                                              \
	                                                                    \
	/* Compute Position and shift */                                    \
	srcs  = (srcprec  + BITS_PER_MP_LIMB-1)/BITS_PER_MP_LIMB;           \
	dests = (destprec + BITS_PER_MP_LIMB-1)/BITS_PER_MP_LIMB;           \
	MPFR_UNSIGNED_MINUS_MODULO (sh, destprec);                          \
	sp = srcp + srcs - dests;                                           \
	                                                                    \
	/* General case when prec % BITS_PER_MP_LIMB != 0 */                \
	if (MPFR_LIKELY (sh != 0))                                          \
	  {                                                                 \
	    mp_limb_t mask;                                                 \
	    /* Compute Rounding Bit and Sticky Bit */                       \
	    mask = MPFR_LIMB_ONE << (sh-1);                                 \
	    rb = sp[0] & mask;                                              \
	    sb = sp[0] & (mask-1);                                          \
	    if (MPFR_UNLIKELY (sb == 0))                                    \
	      { /* TODO: Improve it */                                      \
		mp_limb_t *tmp;                                             \
		mp_size_t n;                                                \
		for (tmp = sp, n = srcs - dests ; n != 0 && sb == 0 ; n--)  \
		  sb = *--tmp;                                              \
	      }                                                             \
	    ulp = 2*mask;                                                   \
	  }                                                                 \
	else /* sh == 0 */                                                  \
	  {                                                                 \
	    MPFR_ASSERTD (dests < srcs);                                    \
	    /* Compute Rounding Bit and Sticky Bit */                       \
	    rb = sp[-1] & MPFR_LIMB_HIGHBIT;                                \
	    sb = sp[-1] & (MPFR_LIMB_HIGHBIT-1);                            \
	    if (MPFR_UNLIKELY (sb == 0))                                    \
	      {                                                             \
		mp_limb_t *tmp;                                             \
		mp_size_t n;                                                \
		for (tmp = sp-1, n = srcs - dests-1 ; n!=0 && sb==0 ; n--)  \
		  sb = *--tmp;                                              \
	      }                                                             \
	    ulp = MPFR_LIMB_ONE;                                            \
	  }                                                                 \
	/* Rounding */                                                      \
	if (MPFR_LIKELY (rnd == GMP_RNDN))                                  \
	  {                                                                 \
	    if (rb == 0)                                                    \
	      {                                                             \
	      trunc:                                                        \
		inexact = MPFR_LIKELY ((sb | rb) != 0) ? -sign : 0;         \
              trunc_doit:                                                   \
		MPN_COPY (destp, sp, dests);                                \
		destp[0] &= ~(ulp-1);                                       \
	      }                                                             \
	    else if (MPFR_UNLIKELY (sb == 0))                               \
	      {                                                             \
	        /* EVEN rounding */                                         \
	        if ((sp[0] & ulp) == 0)                                     \
		 {                                                          \
		  MPFR_ASSERTD (rb != 0);                                   \
		  inexact = -MPFR_EVEN_INEX*sign;                           \
		  goto trunc_doit;                                          \
		 }                                                          \
	        else                                                        \
		 {                                                          \
		  inexact = MPFR_EVEN_INEX*sign;                            \
		  goto addoneulp_doit;                                      \
		 }                                                          \
	      }                                                             \
	    else                                                            \
              {                                                             \
	      addoneulp:                                                    \
                inexact = sign;                                             \
              addoneulp_doit:                                               \
		if (MPFR_UNLIKELY (mpn_add_1 (destp, sp, dests, ulp)))      \
		  {                                                         \
		    destp[dests-1] = MPFR_LIMB_HIGHBIT;                     \
		    OVERFLOW_HANDLER;                                       \
		  }                                                         \
		destp[0] &= ~(ulp-1);                                       \
	      }                                                             \
	  }                                                                 \
	else                                                                \
	  { /* Not Rounding to Nearest */                                   \
	    if (MPFR_LIKELY (MPFR_IS_LIKE_RNDZ (rnd, MPFR_IS_NEG_SIGN (sign)))\
		|| MPFR_UNLIKELY ((sb | rb) == 0))                          \
	      goto trunc;                                                   \
	     else                                                           \
	      goto addoneulp;                                               \
	  }                                                                 \
      }                                                                     \
  } while (0)

/* Return TRUE if b is non singular and we can round it to precision 'prec'
   with rounding mode 'rnd', and with error at most 'error' */
#define MPFR_CAN_ROUND(b,err,prec,rnd)                                       \
 (!MPFR_IS_SINGULAR (b) && mpfr_round_p (MPFR_MANT (b), MPFR_LIMB_SIZE (b),  \
					 (err), (prec) + ((rnd)==GMP_RNDN)))

/* Assuming that the function as a taylor expansion which looks like:
    y=f(x) = x + g(x) with |g(x)| <=2^(EXP(x)-err)
   we can quickly set y to x if x is small (ie nearly err > prec(y)+1).
   It assumes that f(x) is not representable exactly as a FP number.  
   y is the destination, x the value to set, err the error term,
    dir the direction (=0 => towards 0, =1 => away), rnd the rounding mode.
   It returns from the function a ternary value in case of success.
   If you want to free something, you must fill the "extra" field
   in consequences, otherwise put nothing. */
/* Note: Use mpfr_round_p (faster but less precise) or mpfr_can_round? */
#define MPFR_FAST_COMPUTE_IF_SMALL_INPUT(y,x,err,dir,rnd,extra) \
  do {                                                          \
   mp_exp_t _err = (err);                                       \
   mp_prec_t _prec = MPFR_PREC (y) + ((rnd) == GMP_RNDN);       \
   if (_err > 0 && (mpfr_uexp_t) _err > _prec                   \
      && (dir == 0                                              \
          || (mpfr_uexp_t) _err > MPFR_PREC (x)                 \
          || mpfr_can_round ((x), _err, GMP_RNDZ, (rnd), MPFR_PREC (y)))) \
    {                                                           \
      int _inexact = mpfr_round_near_x ((y),(x),(dir),(rnd));   \
      extra;                                                    \
      return _inexact;                                          \
    }                                                           \
  } while (0)

/******************************************************
 ***************  Ziv Loop Macro  *********************
 ******************************************************/

#ifndef MPFR_USE_LOGGING

#define MPFR_ZIV_DECL(_x) mp_prec_t _x
#define MPFR_ZIV_INIT(_x, _p) (_x) = BITS_PER_MP_LIMB
#define MPFR_ZIV_NEXT(_x, _p) ((_p) += (_x), (_x) = (_p)/2)
#define MPFR_ZIV_FREE(x)

#else
/* Use LOGGING */
#define MPFR_ZIV_DECL(_x)                                     \
  mp_prec_t _x;                                               \
  int _x ## _cpt = 1;                                         \
  static unsigned long  _x ## _loop = 0, _x ## _bad = 0;      \
  static const char *_x ## _fname = __func__;                 \
  static void _x ## _f (void) __attribute__ ((destructor));   \
  static void _x ## _f (void) { if (_x ## _loop != 0)         \
     fprintf (mpfr_log_file,                                  \
    "%s: Ziv failed %2.2f%% (%lu bad cases / %lu calls)\n", _x ## _fname,     \
       (double) 100.0 * _x ## _bad / _x ## _loop,  _x ## _bad, _x ## _loop ); }

#define MPFR_ZIV_INIT(_x, _p) ((_x) = BITS_PER_MP_LIMB, _x ## _loop ++);     \
  if (MPFR_LOG_BADCASE_F&mpfr_log_type && mpfr_log_current<=mpfr_log_level)  \
   fprintf (mpfr_log_file, "%s:ZIV 1st prec=%lu\n", __func__,                \
            (unsigned long) (_p))

#define MPFR_ZIV_NEXT(_x, _p)                                                \
 ((_p)+=(_x),(_x)=(_p)/2, _x ## _bad += (_x ## _cpt == 1), _x ## _cpt ++);   \
  if (MPFR_LOG_BADCASE_F&mpfr_log_type && mpfr_log_current<=mpfr_log_level)  \
   fprintf (mpfr_log_file, "%s:ZIV new prec=%lu\n", __func__,                \
     (unsigned long) (_p))
  
#define MPFR_ZIV_FREE(_x)                                             \
  if (MPFR_LOG_BADCASE_F&mpfr_log_type && _x##_cpt>1                  \
      && mpfr_log_current<=mpfr_log_level)                            \
   fprintf (mpfr_log_file, "%s:ZIV %d loops\n", __func__, _x ## _cpt)

#endif


/******************************************************
 ***************  Logging Macros  *********************
 ******************************************************/

/* The different kind of LOG */
#define MPFR_LOG_INPUT_F    1
#define MPFR_LOG_OUTPUT_F   2
#define MPFR_LOG_INTERNAL_F 4
#define MPFR_LOG_TIME_F     8
#define MPFR_LOG_BADCASE_F  16
#define MPFR_LOG_MSG_F      32

#ifdef MPFR_USE_LOGGING

# include <stdio.h>

/* Check if we can support this feature */
# ifdef MPFR_USE_THREAD_SAFE
#  error "Enable either `Logging' or `thread-safe', not both"
# endif 
# if !__MPFR_GNUC(3,0)
#  error "Logging not supported (GCC >= 3.0)"
# endif

#if defined (__cplusplus)
extern "C" {
#endif

__MPFR_DECLSPEC extern FILE *mpfr_log_file;
__MPFR_DECLSPEC extern int   mpfr_log_type;
__MPFR_DECLSPEC extern int   mpfr_log_level;
__MPFR_DECLSPEC extern int   mpfr_log_current;
__MPFR_DECLSPEC extern int   mpfr_log_base;
__MPFR_DECLSPEC extern mp_prec_t mpfr_log_prec;

#if defined (__cplusplus)
 }
#endif

#define MPFR_LOG_VAR(x)                                                      \
  if((MPFR_LOG_INTERNAL_F&mpfr_log_type)&&(mpfr_log_current<=mpfr_log_level))\
   fprintf (mpfr_log_file, "%s.%d:%s[%#R]=%R\n", __func__,__LINE__, #x, x, x);

#define MPFR_LOG_MSG2(format, ...)                                       \
 if ((MPFR_LOG_MSG_F&mpfr_log_type)&&(mpfr_log_current<=mpfr_log_level)) \
  fprintf (mpfr_log_file, "%s.%d:"format, __func__, __LINE__, __VA_ARGS__);
#define MPFR_LOG_MSG(x) MPFR_LOG_MSG2 x

#define MPFR_LOG_BEGIN2(format, ...)                                         \
  mpfr_log_current ++;                                                       \
  if ((MPFR_LOG_INPUT_F&mpfr_log_type)&&(mpfr_log_current<=mpfr_log_level))  \
    fprintf (mpfr_log_file, "%s:IN  "format"\n",__func__,__VA_ARGS__);       \
  if ((MPFR_LOG_TIME_F&mpfr_log_type)&&(mpfr_log_current<=mpfr_log_level))   \
    __gmpfr_log_time = mpfr_get_cputime ();
#define MPFR_LOG_BEGIN(x)                                                    \
  int __gmpfr_log_time = 0;                                                  \
  MPFR_LOG_BEGIN2 x

#define MPFR_LOG_END2(format, ...)                                           \
  if ((MPFR_LOG_TIME_F&mpfr_log_type)&&(mpfr_log_current<=mpfr_log_level))   \
    fprintf (mpfr_log_file, "%s:TIM %dms\n", __mpfr_log_fname,               \
	     mpfr_get_cputime () - __gmpfr_log_time);                        \
  if ((MPFR_LOG_OUTPUT_F&mpfr_log_type)&&(mpfr_log_current<=mpfr_log_level)) \
    fprintf (mpfr_log_file, "%s:OUT "format"\n",__mpfr_log_fname,__VA_ARGS__);\
  mpfr_log_current --;
#define MPFR_LOG_END(x)                                                     \
  static const char *__mpfr_log_fname = __func__;                           \
  MPFR_LOG_END2 x

#define MPFR_LOG_FUNC(begin,end)                                            \
  static const char *__mpfr_log_fname = __func__;                           \
  static void __mpfr_log_cleanup (int *time) {                              \
    int __gmpfr_log_time = *time;                                           \
    MPFR_LOG_END2 end; }                                                    \
  int __gmpfr_log_time __attribute__ ((cleanup (__mpfr_log_cleanup)));      \
  __gmpfr_log_time = 0;                                                     \
  MPFR_LOG_BEGIN2 begin

#else /* MPFR_USE_LOGGING */

/* Define void macro for logging */

#define MPFR_LOG_VAR(x)
#define MPFR_LOG_BEGIN(x)
#define MPFR_LOG_END(x)
#define MPFR_LOG_MSG(x)
#define MPFR_LOG_FUNC(x,y)

#endif /* MPFR_USE_LOGGING */


/**************************************************************
 ***************  Group Functions Macros  *********************
 **************************************************************/

#define MPFR_GROUP_DECL() mp_limb_t *mpfr_group_mant; size_t mpfr_group_alloc
#define I(x) ((mpfr_group_mode == 0) ? ++mpfr_group_count :              \
 MPFR_TMP_INIT1 (mpfr_group_mant + mpfr_group_size*(mpfr_group_count++), \
 x, mpfr_group_prec))
#define MPFR_GROUP_INIT(prec, group) do {                                    \
 mp_prec_t mpfr_group_prec = (prec);                                         \
 mp_size_t mpfr_group_size;                                                  \
 int mpfr_group_mode = 0, mpfr_group_count = 0;                              \
 mpfr_group_size = (mpfr_group_prec +BITS_PER_MP_LIMB-1)/BITS_PER_MP_LIMB;   \
 group;                                                                      \
 mpfr_group_alloc = mpfr_group_count*mpfr_group_size;                        \
 mpfr_group_mant = (*__gmp_allocate_func) (mpfr_group_alloc);                \
 mpfr_group_mode = 1; mpfr_group_count = 0;                                  \
 group;                                                                      \
 } while (0)
#define MPFR_GROUP_REPREC(prec, group) do {                                  \
 mp_prec_t mpfr_group_prec = (prec);                                         \
 size_t    mpfr_group_oalloc = mpfr_group_alloc;                             \
 mp_size_t mpfr_group_size;                                                  \
 int mpfr_group_mode = 0, mpfr_group_count = 0;                              \
 mpfr_group_size = (mpfr_group_prec +BITS_PER_MP_LIMB-1)/BITS_PER_MP_LIMB;   \
 group;                                                                      \
 mpfr_group_alloc = mpfr_group_count*mpfr_group_size;                        \
 mpfr_group_mant = (*__gmp_reallocate_func)(mpfr_group_mant,                 \
					    mpfr_group_oalloc,               \
					    mpfr_group_alloc);               \
 mpfr_group_mode = 1; mpfr_group_count = 0;                                  \
 group;                                                                      \
} while (0)
#define MPFR_GROUP_CLEAR()                                                   \
 do { (*__gmp_free_func)(mpfr_group_mant, mpfr_group_alloc);} while (0)


/******************************************************
 ***************  Internal Functions  *****************
 ******************************************************/

#if defined (__cplusplus)
extern "C" {
#endif

#ifdef HAVE_STRCASECMP
__MPFR_DECLSPEC int strcasecmp _MPFR_PROTO ((const char *, const char *));
#else
__MPFR_DECLSPEC int mpfr_strcasecmp _MPFR_PROTO ((const char*, const char*));
#endif

#ifdef HAVE_STRNCASECMP
__MPFR_DECLSPEC int strncasecmp _MPFR_PROTO((const char*,const char*,size_t));
#else
__MPFR_DECLSPEC int mpfr_strncasecmp _MPFR_PROTO ((const char *, 
						   const char *, size_t));
#endif

__MPFR_DECLSPEC int mpfr_underflow _MPFR_PROTO ((mpfr_ptr, mp_rnd_t, int));
__MPFR_DECLSPEC int mpfr_overflow _MPFR_PROTO ((mpfr_ptr, mp_rnd_t, int));

__MPFR_DECLSPEC int mpfr_add1 _MPFR_PROTO ((mpfr_ptr, mpfr_srcptr, 
					    mpfr_srcptr, mp_rnd_t));
__MPFR_DECLSPEC int mpfr_sub1 _MPFR_PROTO ((mpfr_ptr, mpfr_srcptr, 
					    mpfr_srcptr, mp_rnd_t));
__MPFR_DECLSPEC int mpfr_add1sp _MPFR_PROTO ((mpfr_ptr, mpfr_srcptr, 
					      mpfr_srcptr, mp_rnd_t));
__MPFR_DECLSPEC int mpfr_sub1sp _MPFR_PROTO ((mpfr_ptr, mpfr_srcptr, 
					      mpfr_srcptr, mp_rnd_t));
__MPFR_DECLSPEC int mpfr_can_round_raw _MPFR_PROTO ((const mp_limb_t *, 
		    mp_size_t, int, mp_exp_t, mp_rnd_t, mp_rnd_t, mp_prec_t));

__MPFR_DECLSPEC int mpfr_cmp2 _MPFR_PROTO ((mpfr_srcptr, mpfr_srcptr,
					    mp_prec_t *));

__MPFR_DECLSPEC long          __gmpfr_ceil_log2     _MPFR_PROTO ((double));
__MPFR_DECLSPEC long          __gmpfr_floor_log2    _MPFR_PROTO ((double));
__MPFR_DECLSPEC double        __gmpfr_ceil_exp2     _MPFR_PROTO ((double));
__MPFR_DECLSPEC unsigned long __gmpfr_isqrt     _MPFR_PROTO ((unsigned long));
__MPFR_DECLSPEC unsigned long __gmpfr_cuberoot  _MPFR_PROTO ((unsigned long));
__MPFR_DECLSPEC int       __gmpfr_int_ceil_log2 _MPFR_PROTO ((unsigned long));

__MPFR_DECLSPEC int mpfr_exp_2 _MPFR_PROTO ((mpfr_ptr, mpfr_srcptr,mp_rnd_t));
__MPFR_DECLSPEC int mpfr_exp_3 _MPFR_PROTO ((mpfr_ptr, mpfr_srcptr,mp_rnd_t));
__MPFR_DECLSPEC int mpfr_powerof2_raw _MPFR_PROTO ((mpfr_srcptr));

__MPFR_DECLSPEC void mpfr_setmax _MPFR_PROTO ((mpfr_ptr, mp_exp_t));
__MPFR_DECLSPEC void mpfr_setmin _MPFR_PROTO ((mpfr_ptr, mp_exp_t));

__MPFR_DECLSPEC long mpfr_mpn_exp _MPFR_PROTO ((mp_limb_t *, mp_exp_t *, int,
			   mp_exp_t, size_t));

__MPFR_DECLSPEC void mpfr_print_binary _MPFR_PROTO ((mpfr_srcptr));
__MPFR_DECLSPEC void mpfr_print_mant_binary _MPFR_PROTO ((const char*,
					  const mp_limb_t*, mp_prec_t));
__MPFR_DECLSPEC void mpfr_set_str_binary _MPFR_PROTO((mpfr_ptr, const char*));

__MPFR_DECLSPEC int mpfr_round_raw _MPFR_PROTO ((mp_limb_t *, 
       const mp_limb_t *, mp_prec_t, int, mp_prec_t, mp_rnd_t, int *));
__MPFR_DECLSPEC int mpfr_round_raw_2 _MPFR_PROTO ((const mp_limb_t *, 
             mp_prec_t, int, mp_prec_t, mp_rnd_t));
__MPFR_DECLSPEC int mpfr_round_raw_3 _MPFR_PROTO ((const mp_limb_t *,
             mp_prec_t, int, mp_prec_t, mp_rnd_t, int *));
__MPFR_DECLSPEC int mpfr_round_raw_4 _MPFR_PROTO ((mp_limb_t *, 
       const mp_limb_t *, mp_prec_t, int, mp_prec_t, mp_rnd_t));

#define mpfr_round_raw2(xp, xn, neg, r, prec) \
  mpfr_round_raw_2((xp),(xn)*BITS_PER_MP_LIMB,(neg),(prec),(r))

__MPFR_DECLSPEC int mpfr_check _MPFR_PROTO ((mpfr_srcptr));

__MPFR_DECLSPEC void mpfr_count_sort _MPFR_PROTO ((mpfr_ptr const [],
 					     unsigned long , mpfr_srcptr *));

__MPFR_DECLSPEC int mpfr_get_cputime _MPFR_PROTO ((void));

__MPFR_DECLSPEC void mpfr_nexttozero _MPFR_PROTO ((mpfr_ptr));
__MPFR_DECLSPEC void mpfr_nexttoinf _MPFR_PROTO ((mpfr_ptr));

__MPFR_DECLSPEC int mpfr_const_pi_internal _MPFR_PROTO ((mpfr_ptr,mp_rnd_t));
__MPFR_DECLSPEC int mpfr_const_log2_internal _MPFR_PROTO((mpfr_ptr,mp_rnd_t));
__MPFR_DECLSPEC int mpfr_const_euler_internal _MPFR_PROTO((mpfr_ptr, mp_rnd_t));
__MPFR_DECLSPEC int mpfr_const_catalan_internal _MPFR_PROTO((mpfr_ptr, mp_rnd_t));
__MPFR_DECLSPEC void mpfr_mulhigh_n _MPFR_PROTO ((mp_ptr, mp_srcptr, 
						  mp_srcptr, mp_size_t));

__MPFR_DECLSPEC int mpfr_round_p _MPFR_PROTO ((mp_limb_t *, mp_size_t, 
					       mp_exp_t, mp_prec_t));

__MPFR_DECLSPEC void mpfr_dump_mant _MPFR_PROTO ((const mp_limb_t *, 
						  mp_prec_t, mp_prec_t,
						  mp_prec_t));

__MPFR_DECLSPEC int mpfr_round_near_x _MPFR_PROTO ((mpfr_ptr, mpfr_srcptr, 
						    int, mp_rnd_t));
#if defined (__cplusplus)
}
#endif

#endif
