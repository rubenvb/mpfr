/* Utilities for MPFR developers, not exported.

Copyright 1999, 2000, 2001, 2002, 2003 Free Software Foundation, Inc.

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

#ifndef HAVE_STRCASECMP
#define strcasecmp mpfr_strcasecmp
#endif

#ifndef HAVE_STRNCASECMP
#define strncasecmp mpfr_strncasecmp
#endif

/* Definition of MPFR_LIMB_HIGHBIT */

#ifdef GMP_LIMB_HIGHBIT
#define MPFR_LIMB_HIGHBIT GMP_LIMB_HIGHBIT
#else
#define MPFR_LIMB_HIGHBIT MP_LIMB_T_HIGHBIT
#endif

#if GMP_NAIL_BITS != 0
#error "MPFR doesn't support nonzero values of GMP_NAIL_BITS"
#endif

/* Test if X (positive) is a power of 2 */

#define IS_POW2(X) (((X) & ((X) - 1)) == 0)
#define NOT_POW2(X) (((X) & ((X) - 1)) != 0)

/* This unsigned type must correspond to the signed one defined in gmp.h */
#if defined (_CRAY) && ! defined (_CRAYMPP)
typedef unsigned int            mp_exp_unsigned_t;
typedef unsigned int            mp_size_unsigned_t;
#else
typedef unsigned long int       mp_exp_unsigned_t;
typedef unsigned long int       mp_size_unsigned_t;
#endif

#define MP_EXP_T_MAX ((mp_exp_t) ((~ (mp_exp_unsigned_t) 0) >> 1))
#define MP_EXP_T_MIN (-MP_EXP_T_MAX-1)

#define MP_LIMB_T_ONE ((mp_limb_t) 1)

#if (BITS_PER_MP_LIMB & (BITS_PER_MP_LIMB - 1))
#error "BITS_PER_MP_LIMB must be a power of 2"
#endif

#define MPFR_INTPREC_MAX (ULONG_MAX & ~(unsigned long) (BITS_PER_MP_LIMB - 1))

/* Assertions */

/* Compile with -DWANT_ASSERT to check all assert statements */

/* Note: do not use GMP macros ASSERT_ALWAYS and ASSERT as they are not
   expressions, and as a consequence, they cannot be used in a for(),
   with a comma operator and so on. */

/* MPFR_ASSERTN(expr): assertions that should always be checked */
/* #define MPFR_ASSERTN(expr) ASSERT_ALWAYS(expr) */
#define MPFR_ASSERTN(expr)  ((void) ((expr) || (ASSERT_FAIL (expr), 0)))

/* MPFR_ASSERTD(expr): assertions that should be checked when testing */
/* #define MPFR_ASSERTD(expr) ASSERT(expr) */
#if WANT_ASSERT
#define MPFR_EXP_CHECK 1
#define MPFR_ASSERTD(expr)  MPFR_ASSERTN (expr)
#else
#define MPFR_ASSERTD(expr)  ((void) 0)
#endif

/* Invalid exponent value (to track bugs...) */
#define MPFR_EXP_INVALID ((mp_exp_t) 1 << 30)

/* Use MPFR_GET_EXP and MPFR_SET_EXP instead of MPFR_EXP directly,
   unless when the exponent may be out-of-range, for instance when
   setting the exponent before calling mpfr_check_range.
   MPFR_EXP_CHECK is defined when WANT_ASSERT is defined, but if you
   don't use WANT_ASSERT (for speed reasons), you can still define
   MPFR_EXP_CHECK by setting -DMPFR_EXP_CHECK in $CFLAGS. */

#if MPFR_EXP_CHECK
#define MPFR_GET_EXP(x)          mpfr_get_exp (x)
#define MPFR_SET_EXP(x, exp)     MPFR_ASSERTN (!mpfr_set_exp ((x), (exp)))
#define MPFR_SET_INVALID_EXP(x)  ((void) (MPFR_EXP (x) = MPFR_EXP_INVALID))
#else
#define MPFR_GET_EXP(x)          MPFR_EXP (x)
#define MPFR_SET_EXP(x, exp)     ((void) (MPFR_EXP (x) = (exp)))
#define MPFR_SET_INVALID_EXP(x)  ((void) 0)
#endif

/* Definition of constants */

#define LOG2 0.69314718055994528622 /* log(2) rounded to zero on 53 bits */
#define ALPHA 4.3191365662914471407 /* a+2 = a*log(a), rounded to +infinity */

/* Safe absolute value (to avoid possible integer overflow) */
/* type is the target (unsigned) type */

#define SAFE_ABS(type,x) ((x) >= 0 ? (type)(x) : -(type)(x))

/* macros for doubles, based on gmp union ieee_double_extract */

#ifndef IEEE_DBL_MANT_DIG
#define IEEE_DBL_MANT_DIG 53
#endif

typedef union ieee_double_extract Ieee_double_extract;

/* for x of type ieee_double_extract */
#define DOUBLE_ISNANorINF(x) (((Ieee_double_extract *)&(x))->s.exp == 0x7ff)
#define DOUBLE_ISINF(x) (DOUBLE_ISNANorINF(x) && \
			 (((Ieee_double_extract *)&(x))->s.manl == 0) && \
                         (((Ieee_double_extract *)&(x))->s.manh == 0))
#define DOUBLE_ISNAN(x) (DOUBLE_ISNANorINF(x) && \
			 ((((Ieee_double_extract *)&(x))->s.manl != 0) || \
                         (((Ieee_double_extract *)&(x))->s.manh != 0)))

#define DBL_POS_INF (1.0/0.0)
#define DBL_NEG_INF (-1.0/0.0)
#define DBL_NAN (0.0/0.0)

/* macros for long doubles */

/* we only require that LDBL_MANT_DIG is a bound on the mantissa length
   of the "long double" type */
#ifndef LDBL_MANT_DIG
#define LDBL_MANT_DIG 113 /* works also if long double == quad */
#endif

/* Various i386 systems have been seen with incorrect LDBL constants in
   float.h (notes in set_ld.c), so force the value we know is right for IEEE
   extended.  */

#if HAVE_LDOUBLE_IEEE_EXT_LITTLE
#define MPFR_LDBL_MANT_DIG   64
#else
#define MPFR_LDBL_MANT_DIG   LDBL_MANT_DIG
#endif

/* LONGDOUBLE_NAN_ACTION executes the code "action" if x is a NaN. */

/* On hppa2.0n-hp-hpux10 with the unbundled HP cc, the test x!=x on a NaN
   has been seen false, meaning NaNs are not detected.  This seemed to
   happen only after other comparisons, not sure what's really going on.  In
   any case we can pick apart the bytes to identify a NaN.  */
#if HAVE_LDOUBLE_IEEE_QUAD_BIG
#define LONGDOUBLE_NAN_ACTION(x, action)                        \
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
#define LONGDOUBLE_NAN_ACTION(x, action)                \
  do {                                                  \
    volatile long double __x = LONGDOUBLE_VOLATILE (x); \
    if ((x) != __x)                                     \
      { action; }                                       \
  } while (0)
#define WANT_LONGDOUBLE_VOLATILE 1
#endif

/* If we don't have a proper "volatile" then volatile is #defined to empty,
   in this case call through an external function to stop the compiler
   optimizing anything. */
#if WANT_LONGDOUBLE_VOLATILE
#ifdef volatile
long double __gmpfr_longdouble_volatile __GMP_PROTO ((long double)) ATTRIBUTE_CONST;
#define LONGDOUBLE_VOLATILE(x)  (__gmpfr_longdouble_volatile (x))
#define WANT_GMPFR_LONGDOUBLE_VOLATILE 1
#else
#define LONGDOUBLE_VOLATILE(x)  (x)
#endif
#endif


/* bit 31 of _mpfr_size is used for sign,
   bit 30 of _mpfr_size is used for Nan flag,
   bit 29 of _mpfr_size is used for Inf flag,
   remaining bits are used to store the number of allocated limbs */
#define MPFR_CLEAR_FLAGS(x) \
  (((x) -> _mpfr_size &= ~((mp_size_unsigned_t) 3 << 29)))
#define MPFR_IS_NAN(x) (((x)->_mpfr_size) & ((mp_size_unsigned_t) 1 << 30))
#define MPFR_SET_NAN(x) \
  (MPFR_SET_INVALID_EXP(x), \
   (x)->_mpfr_size |= ((mp_size_unsigned_t) 1 << 30))
#define MPFR_CLEAR_NAN(x) \
  (((x) -> _mpfr_size &= ~((mp_size_unsigned_t) 1 << 30)))
#define MPFR_IS_INF(x) (((x)->_mpfr_size) & ((mp_size_unsigned_t) 1 << 29))
#define MPFR_SET_INF(x) \
  (MPFR_SET_INVALID_EXP(x), \
   (x)->_mpfr_size |= ((mp_size_unsigned_t) 1 << 29))
#define MPFR_CLEAR_INF(x) ((x)->_mpfr_size &= ~((mp_size_unsigned_t) 1 << 29))
#define MPFR_IS_FP(x) \
  ((((x) -> _mpfr_size) & ((mp_size_unsigned_t) 3 << 29)) == 0)
#define MPFR_ABSSIZE(x) \
  ((x)->_mpfr_size & (((mp_size_unsigned_t) 1 << 29) - 1))
#define MPFR_SET_ABSSIZE(x, n) \
  ((x)->_mpfr_size = ((x)->_mpfr_size & ((mp_size_unsigned_t) 7 << 29)) \
                     | (mp_size_unsigned_t) (n))
#define MPFR_SIZE(x) ((x)->_mpfr_size)
#define MPFR_EXP(x) ((x)->_mpfr_exp)
#define MPFR_MANT(x) ((x)->_mpfr_d)
#define MPFR_ISNONNEG(x) (MPFR_NOTZERO((x)) && MPFR_SIGN(x) >= 0)
#define MPFR_ISNEG(x) (MPFR_NOTZERO((x)) && MPFR_SIGN(x) == -1)
#define MPFR_SET_POS(x) (MPFR_SIZE(x) &= ~(((mp_size_unsigned_t) 1) << 31))
#define MPFR_SET_NEG(x) (MPFR_SIZE(x) |= (((mp_size_unsigned_t) 1) << 31))
#define MPFR_CHANGE_SIGN(x) (MPFR_SIZE(x) ^= (((mp_size_unsigned_t) 1) << 31))
#define MPFR_SET_SAME_SIGN(x, y) \
  (MPFR_SIGN((x)) != MPFR_SIGN((y)) && (MPFR_CHANGE_SIGN((x)), 0))
#define MPFR_PREC(x) ((x)->_mpfr_prec)
#define MPFR_NOTZERO(x) \
  (MPFR_MANT(x)[(MPFR_PREC(x)-1)/BITS_PER_MP_LIMB] != (mp_limb_t) 0)
#define MPFR_IS_ZERO(x) \
  (MPFR_MANT(x)[(MPFR_PREC(x)-1)/BITS_PER_MP_LIMB] == (mp_limb_t) 0)
#define MPFR_SET_ZERO(x) \
  (MPFR_SET_INVALID_EXP(x), \
   MPFR_MANT(x)[(MPFR_PREC(x)-1)/BITS_PER_MP_LIMB] = (mp_limb_t) 0)
#define MPFR_ESIZE(x) \
  ((MPFR_PREC((x)) - 1) / BITS_PER_MP_LIMB + 1)
#define MPFR_EVEN_INEX 2

/* When returning the ternary inexact value, ALWAYS use one of the
   following two macros, unless the flag comes from another function
   returning the ternary inexact value */
#define MPFR_RET(I) return \
  (I) ? ((__gmpfr_flags |= MPFR_FLAGS_INEXACT), (I)) : 0
#define MPFR_RET_NAN return (__gmpfr_flags |= MPFR_FLAGS_NAN), 0

/* Memory gestion */

/* temporary allocate s limbs at xp, and initialize mpfr variable x */
#define MPFR_INIT(xp, x, p, s) \
  (xp = (mp_ptr) TMP_ALLOC((size_t) (s) * BYTES_PER_MP_LIMB), \
   MPFR_PREC(x) = (p), \
   MPFR_MANT(x) = (xp), \
   MPFR_SIZE(x) = (s), \
   MPFR_SET_INVALID_EXP(x))
/* same when xp is already allocated */
#define MPFR_INIT1(xp, x, p, s) \
  (MPFR_PREC(x) = (p), MPFR_MANT(x) = (xp), MPFR_SIZE(x) = (s))

#ifndef _PROTO
#if defined (__STDC__) || defined (__cplusplus)
#define _PROTO(x) x
#else
#define _PROTO(x) ()
#endif
#endif

#if defined (__cplusplus)
extern "C" {
#endif

extern mpfr_t __mpfr_const_log2;
extern mp_prec_t __gmpfr_const_log2_prec;

extern mpfr_t __mpfr_const_pi;
extern mp_prec_t __gmpfr_const_pi_prec;

#ifdef HAVE_STRCASECMP
int strcasecmp _PROTO ((const char *, const char *));
#else
int mpfr_strcasecmp _PROTO ((const char *, const char *));
#endif

#ifdef HAVE_STRNCASECMP
int strncasecmp _PROTO ((const char *, const char *, size_t));
#else
int mpfr_strncasecmp _PROTO ((const char *, const char *, size_t));
#endif

void mpfr_inits2 _PROTO ((mp_prec_t, mpfr_ptr, ...));
void mpfr_inits _PROTO ((mpfr_ptr, ...));
void mpfr_clears _PROTO ((mpfr_ptr, ...));

int mpfr_set_underflow _PROTO ((mpfr_ptr, mp_rnd_t, int));
int mpfr_set_overflow _PROTO ((mpfr_ptr, mp_rnd_t, int));
void mpfr_save_emin_emax _PROTO ((void));
void mpfr_restore_emin_emax _PROTO ((void));
int mpfr_add1 _PROTO ((mpfr_ptr, mpfr_srcptr, mpfr_srcptr,
                       mp_rnd_t, mp_exp_unsigned_t));
int mpfr_sub1 _PROTO ((mpfr_ptr, mpfr_srcptr, mpfr_srcptr,
                       mp_rnd_t, int));
int mpfr_round_raw_generic _PROTO ((mp_limb_t *, mp_limb_t *, mp_prec_t, int,
				    mp_prec_t, mp_rnd_t, int *, int));
int mpfr_can_round_raw _PROTO ((mp_limb_t *, mp_size_t, int, mp_exp_t,
				mp_rnd_t, mp_rnd_t, mp_prec_t));
double mpfr_get_d3 _PROTO ((mpfr_srcptr, mp_exp_t, mp_rnd_t));
int mpfr_cmp2 _PROTO ((mpfr_srcptr, mpfr_srcptr, mp_prec_t *));
long __gmpfr_ceil_log2 _PROTO ((double));
long __gmpfr_floor_log2 _PROTO ((double));
double __gmpfr_ceil_exp2 _PROTO ((double));
unsigned long __gmpfr_isqrt _PROTO ((unsigned long));
unsigned long __gmpfr_cuberoot _PROTO ((unsigned long));
int mpfr_exp_2 _PROTO ((mpfr_ptr, mpfr_srcptr, mp_rnd_t));
int mpfr_exp3 _PROTO ((mpfr_ptr, mpfr_srcptr, mp_rnd_t));
int mpfr_powerof2_raw _PROTO ((mpfr_srcptr));
void mpfr_setmax _PROTO ((mpfr_ptr, mp_exp_t));
void mpfr_setmin _PROTO ((mpfr_ptr, mp_exp_t));
long mpn_exp _PROTO ((mp_limb_t *, mp_exp_t *, int, mp_exp_t, size_t));
void mpfr_print_binary _PROTO ((mpfr_srcptr));
void mpfr_set_str_binary _PROTO ((mpfr_ptr, __gmp_const char *));

#define mpfr_round_raw(yp, xp, xprec, neg, yprec, r, inexp) \
  mpfr_round_raw_generic((yp), (xp), (xprec), (neg), (yprec), (r), (inexp), 0)

#define mpfr_round_raw2(xp, xn, neg, r, prec) \
  mpfr_round_raw_generic(0, (xp), (xn) * BITS_PER_MP_LIMB, (neg), \
			 (prec), (r), 0, 1);

#if defined (__cplusplus)
}
#endif