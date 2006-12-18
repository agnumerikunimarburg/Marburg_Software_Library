// -*- c++ -*-

// +--------------------------------------------------------------------+
// | This file is part of WaveletTL - the Wavelet Template Library      |
// |                                                                    |
// | Copyright (c) 2002-2006                                            |
// | Thorsten Raasch, Manuel Werner                                     |
// +--------------------------------------------------------------------+

#ifndef _WAVELETTL_LDOMAIN_JL_EVALUATE_H
#define _WAVELETTL_LDOMAIN_JL_EVALUATE_H

#include <utils/array1d.h>
#include <geometry/sampled_mapping.h>
#include <algebra/infinite_vector.h>
#include <Ldomain/ldomain_jl_basis.h>

using MathTL::Array1D;
using MathTL::SampledMapping;
using MathTL::InfiniteVector;

namespace WaveletTL
{
  typedef LDomainJLBasis::Index Index;
    
  /*!
    Evaluate a single primal generator or wavelet \psi_\lambda
    on a dyadic subgrid of the L-shaped domain
  */
  Array1D<SampledMapping<2> >
  evaluate(const LDomainJLBasis& basis,
	   const Index& lambda,
	   const int resolution);
    
  /*!
    Evaluate an arbitrary linear combination of primal wavelets
    on a dyadic subgrid of the L-shaped domain
  */
  Array1D<SampledMapping<2> >
  evaluate(const LDomainJLBasis& basis,
	   const InfiniteVector<double, Index>& coeffs,
	   const int resolution);
}

#include <Ldomain/ldomain_jl_evaluate.cpp>

#endif
