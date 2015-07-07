#include "lombscargle.h"
#include <math.h>

void Analyse::lombscargle(double* t, double* x, double* w, double* P, int Nt, int Nw)
{
  /**
   *  Purpose
   *  =======
   *
   *  Computes the Lomb-Scargle periodogram as developed by Lomb (1976)
   *  and further extended by Scargle (1982) to find, and test the
   *  significance of weak periodic signals with uneven temporal sampling.
   *
   *  This subroutine calculates the periodogram using a slightly
   *  modified algorithm due to Townsend (2010) which allows the
   *  periodogram to be calculated using only a single pass through
   *  the input samples.
   *  This requires Nw(2Nt+3) trigonometric function evaluations (where
   *  Nw is the number of frequencies and Nt the number of input samples),
   *  giving a factor of ~2 speed increase over the straightforward
   *  implementation.
   *
   *  Arguments
   *  =========
   *
   *  t   (input) double precision array, dimension (Nt)
   *      Sample times
   *
   *  x   (input) double precision array, dimension (Nt)
   *      Measurement values
   *
   *  w   (input) double precision array, dimension (Nt)
   *      Angular frequencies for output periodogram
   *
   *  P   (output) double precision array, dimension (Nw)
   *      Lomb-Scargle periodogram
   *
   *  Nt (input) integer
   *      Dimension of input arrays
   *
   *  Nw (output) integer
   *      Dimension of output array
   *
   *  Further details
   *  ===============
   *
   *  P[i] takes a value of A^2*N/4 for a harmonic signal with
   *  frequency w(i).
   **/

  /* Local variables */
  int i, j;
  double c, s, xc, xs, cc, ss, cs;
  double tau, c_tau, s_tau, c_tau2, s_tau2, cs_tau;
  double term0, term1;

  /* Get pointers to input arrays (faster than array indexing)
     Note that all arrays should be contiguous which is taken care of
     by f2py */
  double* tp = t;
  double* xp = x;

  /* Use x86 decrement and compare to zero instruction (farster than ++) */
  i = Nw;
  while (--i)
  {
    xc = 0.;
    xs = 0.;
    cc = 0.;
    ss = 0.;
    cs = 0.;

    /* (Re)set pointers to start of input arrays */
    tp = t;
    xp = x;

    j = Nt;
    while (--j)
    {
      c = cos(*w * *tp);
      s = sin(*w * *tp);

      xc += *xp * c;
      xs += *xp * s;
      cc += c * c;
      ss += s * s;
      cs += c * s;

      /* Next element in input arrays */
      ++tp;
      ++xp;
    }

    tau = atan(2 * cs / (cc - ss)) / (2 * *w);
    c_tau = cos(*w * tau);
    s_tau = sin(*w * tau);
    c_tau2 = c_tau * c_tau;
    s_tau2 = s_tau * s_tau;
    cs_tau = 2 * c_tau * s_tau;

    term0 = c_tau * xc + s_tau * xs;
    term1 = c_tau * xs - s_tau * xc;
    *P = 0.5 * (((term0 * term0) / \
                   (c_tau2 * cc + cs_tau * cs + s_tau2 * ss)) + \
                  ((term1 * term1) / \
                   (c_tau2 * ss - cs_tau * cs + s_tau2 * cc)));

    /* Next frequency */
    ++w;
    ++P;
  }
}
