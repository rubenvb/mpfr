/* used by mpfr_get_str and mpfr_set_str */

/* for 2 <= b <= 36, log_b2[b-2] + log_b2_low[b-2] is a 76-bit upper 
   approximation of log(2)/log(b), with log_b2[b-2] having 23 significative
   bits only. These approximations were computed with the following program.

#include <stdio.h>
#include "gmp.h"
#include "mpfr.h"

double log_b2[35], log_b2_low[35];

main()
{
  int beta;
  mpfr_t l, l0;

  for (beta=2;beta<=36;beta++)
    {
      mpfr_init2 (l, 77);
      mpfr_set_ui (l, beta, GMP_RNDD);
      mpfr_log2 (l, l, GMP_RNDD);
      mpfr_ui_div (l, 1, l, GMP_RNDU);
      mpfr_init2 (l0, 23);
      mpfr_set (l0, l, GMP_RNDD);
      mpfr_sub (l, l, l0, GMP_RNDU);
      mpfr_prec_round (l, 53, GMP_RNDU);
      log_b2[beta-2] = mpfr_get_d (l0, GMP_RNDU);
      log_b2_low[beta-2] = mpfr_get_d (l, GMP_RNDU);
      mpfr_clear (l0);
      mpfr_clear (l);
    }

  printf ("static const double log_b2[35] = {");
  for (beta=2;beta<=36;beta++)
    {
      printf ("\n%1.20e", log_b2[beta-2]);
      if (beta < 36) printf (",");
    }
  printf ("\n};\n");

  printf ("static const double log_b2_low[35] = {");
  for (beta=2;beta<=36;beta++)
    {
      printf ("\n%1.20e", log_b2_low[beta-2]);
      if (beta < 36) printf (",");
    }
  printf ("\n};\n");
}
*/

static const double log_b2_low[35] = {
  0.00000000000000000000e+00,
  4.50906224761620348192e-08,
  0.00000000000000000000e+00,
  3.82026349940294905572e-08,
  6.38844173335462308442e-09,
  5.47685446374516835508e-08,
  1.98682149251302105391e-08,
  2.25453112380810174096e-08,
  1.54813334901356166450e-08,
  1.73674161903183898500e-09,
  3.03180611272229558617e-09,
  5.29449283838722401896e-08,
  5.85090258233695360801e-08,
  4.12271221790330610183e-09,
  0.00000000000000000000e+00,
  2.91844949512882013763e-08,
  3.04617404727474892263e-09,
  1.11983643106657188415e-08,
  1.54897762641074502508e-08,
  2.61761247509117662805e-08,
  4.50398291018069050027e-09,
  1.28799738389232369510e-08,
  1.89047057535652783545e-08,
  1.91013174970147452786e-08,
  2.94215882512624420131e-08,
  2.49643149546191168760e-08,
  2.00493274507626165734e-08,
  1.61590886321114899524e-08,
  1.47626363632181082532e-09,
  1.34104842501325808254e-08,
  1.19209289550781256617e-08,
  2.51706771840338761560e-10,
  2.74945871340834855649e-08,
  7.23962676182708790191e-09,
  3.19422086667731154221e-09
};

static const double log_b2[35] = {
  1.00000000000000000000e+00,
  6.30929708480834960938e-01,
  5.00000000000000000000e-01,
  4.30676519870758056641e-01,
  3.86852800846099853516e-01,
  3.56207132339477539062e-01,
  3.33333313465118408203e-01,
  3.15464854240417480469e-01,
  3.01029980182647705078e-01,
  2.89064824581146240234e-01,
  2.78942942619323730469e-01,
  2.70238101482391357422e-01,
  2.62649476528167724609e-01,
  2.55958020687103271484e-01,
  2.50000000000000000000e-01,
  2.44650512933731079102e-01,
  2.39812463521957397461e-01,
  2.35408902168273925781e-01,
  2.31378197669982910156e-01,
  2.27670222520828247070e-01,
  2.24243819713592529297e-01,
  2.21064716577529907227e-01,
  2.18104273080825805664e-01,
  2.15338259935379028320e-01,
  2.12746024131774902344e-01,
  2.10309892892837524414e-01,
  2.08014577627182006836e-01,
  2.05846816301345825195e-01,
  2.03795045614242553711e-01,
  2.01849073171615600586e-01,
  1.99999988079071044922e-01,
  1.98239862918853759766e-01,
  1.96561604738235473633e-01,
  1.94959014654159545898e-01,
  1.93426400423049926758e-01
};

