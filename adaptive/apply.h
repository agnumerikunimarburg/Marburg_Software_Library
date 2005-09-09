// -*- c++ -*-

// +--------------------------------------------------------------------+
// | This file is part of WaveletTL - the Wavelet Template Library      |
// |                                                                    |
// | Copyright (c) 2002-2005                                            |
// | Thorsten Raasch                                                    |
// +--------------------------------------------------------------------+

#ifndef _WAVELETTL_APPLY_H
#define _WAVELETTL_APPLY_H

#include <algebra/infinite_vector.h>

namespace WaveletTL
{
  /*!
    Apply the stiffness matrix A of an infinite-dimensional equation

      Au = f

    to a given vector v within a specified target accuracy,

      ||w-Av|| <= eta.
      
    The matrix A is assumed to be s^*-compressible, i.e., for a given k,
    there exists a matrix A_k with at most alpha_k*2^k nonzero entries
    per row and column, so that

      ||A-A_k|| <= alpha_k * 2^{-ks} <= alpha * 2^{-ks}

    for s < s^*.

    The template argument PROBLEM should provide the routine

      void add_column(const double factor,
                      const typename PROBLEM::WaveletBasis::Index& lambda,
		      const int J,
                      InfiniteVector<double,typename PROBLEM::WaveletBasis::Index>& w) const

    which realizes the compression strategy from [CDD1] for the lambda-th column
    of the stiffness matrix A, with compression parameter J, i.e.,
    adds a constant multiple of the compressed column to the vector w.
    The background for this responsibility is that for integral equations,
    both a compression in scale and space has to be performed, while
    for differential equations, only a compression in scale is needed,
    see [CDD1, Prop. 3.4]. Since the algorithm APPLY has to stay as generic as
    possible, the concrete compression strategy should be performed in
    the concrete problem class.
    Moreover, the class PROBLEM has to provide the routines

      double s_star() const
      double alpha() const

    to model the compressibility (constants) of A.

    An example of the template parameter PROBLEM is the template class
    SturmEquation<WBASIS>.

    References:
    [B]    Barinka:
           Fast Computation Tools for Adaptive Wavelet Schemes
    [BDD]  Barinka/Dahlke/Dahmen:
           Adaptive Application of Operators in Standard Representation.
    [CDD1] Cohen/Dahmen/DeVore:
           Adaptive Wavelet Methods for Elliptic Operator Equations - Convergence Rates
    [S]    Stevenson:
           Adaptive Solution of Operator Equations using Wavelet Frames
  */
  template <class PROBLEM>
  void APPLY(const PROBLEM& P,
	     const InfiniteVector<double, typename PROBLEM::WaveletBasis::Index>& v,
	     const double eta,
	     InfiniteVector<double, typename PROBLEM::WaveletBasis::Index>& w);

  /*!
    APPLY with successive COARSE
  */
  template <class PROBLEM>
  void APPLY_COARSE(const PROBLEM& P,
		    const InfiniteVector<double, typename PROBLEM::WaveletBasis::Index>& v,
		    const double eta,
		    InfiniteVector<double, typename PROBLEM::WaveletBasis::Index>& w,
		    const double lambda = 0.5)
  {
    InfiniteVector<double, typename PROBLEM::WaveletBasis::Index> help;
    APPLY(P, v, lambda*eta, help);
    help.COARSE((1-lambda)*eta, w);
  }
}

#include <adaptive/apply.cpp>

#endif
