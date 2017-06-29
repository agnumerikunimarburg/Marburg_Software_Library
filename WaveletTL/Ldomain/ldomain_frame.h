// -*- c++ -*-

// +--------------------------------------------------------------------+
// | This file is part of WaveletTL - the Wavelet Template Library      |
// |                                                                    |
// | Copyright (c) 2002-2009                                            |
// | Thorsten Raasch, Manuel Werner                                     |
// +--------------------------------------------------------------------+

#ifndef _WAVELETTL_LDOMAIN_FRAME_H
#define _WAVELETTL_LDOMAIN_FRAME_H

#include <map>

#include <algebra/vector.h>
#include <algebra/infinite_vector.h>
#include <algebra/sparse_matrix.h>
#include <algebra/block_matrix.h>
#include <geometry/sampled_mapping.h>
#include <utils/fixed_array1d.h>
#include <utils/multiindex.h>

#include <Ldomain/ldomain_frame_index.h>

// for convenience, include also some functionality
#include <Ldomain/ldomain_support.h>

using std::map;
using std::set;
using MathTL::FixedArray1D;
using MathTL::InfiniteVector;
using MathTL::SparseMatrix;
using MathTL::BlockMatrix;

namespace WaveletTL
{
  /*!
    Template class for composite quarklet frames over the L-shaped domain
      (-1,1)^2 \ (0,1)^2
    such that the primal and the dual frame fulfill homogeneous Dirichlet b.c.'s
    on the outer domain boundary.

    References:
     [CDFS13] Piecewise Tensor Product Wavelet Bases by Extensions and Approximation Rates
              N. Chegini, S. Dahlke, U. Friedrich, R. Stevenson
              Mathematics of Computation 82 (2013), 2157-2190. 
     
  */
  template <class IFRAME>
  class LDomainFrame
  {
  public:
      
    //! type of the interval frame
    typedef IFRAME IntervalFrame;
    
//    typedef LDomainFrameIndex<IFRAME> Index;
    
    //! quarklet index class
    typedef LDomainFrameIndex<IntervalFrame> Index;
    typedef typename Index::level_type level_type;
    typedef typename Index::polynomial_type polynomial_type;
    typedef typename Index::type_type type_type;
    

    //! default constructor
    LDomainFrame();

    //! constructor with a precomputed 1D frame
    LDomainFrame(const IntervalFrame& frame1d);

    //! coarsest possible level j0
    inline const level_type& j0() const { return j0_; }
    
    

    //! geometric type of the support sets
    typedef struct {
      int j[2];       // granularity
      int xmin[3];
      int xmax[3];
      int ymin[3];
      int ymax[3];
    } Support;
    
//    inline std::ostream& operator << (std::ostream& os,
//                                      const typename  Support& supp)
//    {
//      using namespace std;
//      
//      os << "("
//         << supp.j[0]
//         << ","
//         << supp.j[1]
//         << ", ["
//         << supp.xmin[0]
//         << ","
//         << supp.xmax[0]
//         << "])";
//      return os;
//    }
    
    

    //! compute the support of psi_lambda, using the internal cache
    void support(const Index& lambda, Support& supp) const;
    
    //! critical Sobolev regularity for the primal generators/quarklets
    static double primal_regularity() { return IntervalFrame::primal_regularity(); } // dirty, we should use max(1.5,~) instead
    
    //! degree of polynomial reproduction for the primal generators/quarklets
    static unsigned int primal_polynomial_degree() { return IntervalFrame::primal_polynomial_degree(); }

    //! number of vanishing moments for the primal quarklets
    static unsigned int primal_vanishing_moments() { return IntervalFrame::primal_vanishing_moments(); }

    //! read access to the underlying 1D frame
    const IntervalFrame& frame1d() const { return frame1d_; }

//    //! size of Delta_j
//    const int Deltasize(const int j) const;
//
//    //! sizes of the different quarklet index sets
//    const int Nabla01size(const int j) const;
//    const int Nabla10size(const int j) const;
//    const int Nabla11size(const int j) const;

    /*!
      The following routines provide read access to the diverse refinement (sub)matrices
      on a level j >= j0. The row and column indices follow the less<Index> ordering.
      Those matrices will be collected in an internal cache to provide faster access.
    */
//    const BlockMatrix<double>&  get_Mj0      (const int j) const;
//    const BlockMatrix<double>&  get_Mj0T     (const int j) const;
//    const SparseMatrix<double>& get_Mj1c_1d  (const int j) const; // initial stable completion in 1D
//    const BlockMatrix<double>&  get_Mj1c_01  (const int j) const;
//    const BlockMatrix<double>&  get_Mj1c_10  (const int j) const;
//    const BlockMatrix<double>&  get_Mj1c_11  (const int j) const;

    //! index of first generator on level j >= j0
    Index first_generator(const level_type& j, const polynomial_type& p = polynomial_type(), const int& number = 0) const;
      
    //! index of last generator on level j >= j0
    Index last_generator(const level_type& j, const polynomial_type& p = polynomial_type()) const;
      
    //! index of first quarklet on level j >= j0
    Index first_quarklet(const level_type& j, const polynomial_type& p = polynomial_type()) const;
      
    //! index of first quarklet on level j >= j0 with type e
    Index first_quarklet(const level_type& j, const type_type& e, const polynomial_type& p = polynomial_type()) const;

    //! index of last quarklet on level j >= j0
    Index last_quarklet(const level_type& j, const polynomial_type& p = polynomial_type()) const;
    
    //! index of last quarklet on level j >= j0
    Index last_quarklet(const int levelsum, const polynomial_type& p = polynomial_type()) const;
    
//    //! Index of last quarklet on level j >= ||j0||_1
//    Index last_quarklet(const int levelsum, const polynomial_type& p = polynomial_type()) const;

    //! RECONSTRUCT routine, simple version
    /*!
      Constructs for a given single quarklet index lambda a coefficient set c,
      such that
      \psi_lambda = \sum_{\lambda'}c_{\lambda'}\psi_{\lambda'}
      where always |\lambda'|>=j
    */
//    void reconstruct_1(const Index& lambda, const int j,
//		       InfiniteVector<double, Index>& c) const;
//
//    //! RECONSTRUCT routine, full version
//    /*!
//      Constructs for a given coefficient set c another one v,
//      such that
//      \sum_{\lambda}c_\lambda\psi_lambda = \sum_{\lambda'}v_{\lambda'}\psi_{\lambda'}
//      where always |\lambda'|>=j
//    */
//    void reconstruct(const InfiniteVector<double, Index>& c, const int j,
//		     InfiniteVector<double, Index>& v) const;

    /*!
      Evaluate a single primal generator or quarklet \psi_\lambda
      on a dyadic subgrid of the L-shaped domain
    */
    Array1D<SampledMapping<2> >
    evaluate
    (const typename LDomainFrame<IntervalFrame>::Index& lambda,
     const int resolution) const;
    
    /*!
      Evaluate an arbitrary linear combination of primal/dual quarklets
      on a dyadic subgrid of the L-shaped domain
    */
    Array1D<SampledMapping<2> >
    evaluate
    (const InfiniteVector<double, typename LDomainFrame<IntervalFrame>::Index>& coeffs,
     const int resolution) const;

    void set_jpmax(const int jmax, const int pmax) {
      jmax_ = jmax;
      pmax_ = pmax;
      setup_full_collection();
    }
    
    inline const int get_jmax() const {
            return jmax_;
        }
        
    inline const  int get_pmax() const {
        return pmax_;
    }

    //! get the quarklet index corresponding to a specified number
    const inline Index* get_quarklet (const int number) const {
      return &full_collection[number];
    }

    //! number of quarklets between coarsest and finest level
    const int degrees_of_freedom() const { return full_collection.size(); };


  protected:
      
    //! Coarsest possible level j0
    level_type j0_;

    //! finest possible level
    int jmax_;
    
    //! highest possible polynomial
    int pmax_;

    //! setup full collectin of quarklets between j0_ and jmax_ as long as a jmax_ has been specified
    void setup_full_collection();

    //! collection of all quarklets between coarsest and finest level
    Array1D<Index> full_collection;

    //! the interval 1d quarklet frame
    IntervalFrame frame1d_;

    //! support cache
    typedef std::map<Index,Support> SupportCache;
    mutable SupportCache supp_cache;

  };
  


}

#include <Ldomain/ldomain_frame.cpp>
//#include <Ldomain/ldomain_evaluate.cpp>
//#include <Ldomain/ldomain_special.cpp>
//#include <Ldomain/ldomain_special_matrices.cpp>

#endif