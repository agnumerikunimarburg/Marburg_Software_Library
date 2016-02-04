#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <algebra/infinite_vector.h>
#include <algebra/sparse_matrix.h>
#include <utils/array1d.h>
#include <utils/fixed_array1d.h>

#include <interval/ds_basis.h>
#include <interval/spline_basis.h>
#include <interval/jl_basis.h>
#include <interval/jl_support.h>
#include <interval/jl_evaluate.h>

#include <cube/cube_basis.h>
#include <cube/cube_support.h>

using namespace std;
using namespace WaveletTL;

int main()
{
  cout << "Testing wavelet bases on the cube..." << endl;

#if 1
  typedef DSBasis<2,2> Basis1D;
  cout << "* a 2D cube basis of DSBasis<2,2> bases:" << endl;
#else
  // this does not work at the moment!!!
  typedef JLBasis Basis1D;
  cout << "* a 2D cube basis of JLBasis bases:" << endl;
#endif

  typedef CubeBasis<Basis1D> Basis;

  typedef Basis::Index Index;
#if 0
  Basis basis;
#else
//   FixedArray1D<int,4> s, sT;
//   s[0] = 1;
//   s[1] = 1;
//   s[2] = 1;
//   s[3] = 1;
//   sT[0] = 0;
//   sT[1] = 0;
//   sT[2] = 0;
//   sT[3] = 0;
//   Basis basis(s, sT);
  FixedArray1D<bool,4> bc;
  bc[0] = bc[1] = true;
  bc[2] = bc[3] = true;
  Basis basis(bc);
#endif

//   basis.set_jmax(basis.j0()+5);
//   for (int i = 0; i < basis.degrees_of_freedom(); i++) {
//     const Index* ind = basis.get_wavelet(i);
//     cout << (*ind) << endl;
//   }



  cout << "- j0=" << basis.j0() << endl;
  cout << "- the default wavelet index: " << Index() << endl;
  cout << "- the default wavelet index w.r.t. the cube basis: " << Index(&basis) << endl;
  cout << "- first generator on the coarsest level: " << first_generator<Basis1D,2,Basis>(&basis, basis.j0()) << endl;
  cout << "- last generator on the coarsest level: " << last_generator<Basis1D,2,Basis>(&basis, basis.j0()) << endl;
  cout << "- first wavelet on the coarsest level: " << first_wavelet<Basis1D,2,Basis>(&basis, basis.j0()) << endl;
  cout << "- last wavelet on the coarsest level: " << last_wavelet<Basis1D,2,Basis>(&basis, basis.j0()) << endl;

#if 1
  cout << "- testing iterator functionality:" << endl;
  for (Index lambda(first_generator<Basis1D,2,Basis>(&basis, basis.j0()));; ++lambda) {
    cout << lambda << endl;
    if (lambda == last_wavelet<Basis1D,2,Basis>(&basis, basis.j0()+1)) break;
  }
#endif

#if 0
  for (int level = basis.j0()+1; level <= basis.j0()+2; level++)
    {
      cout << "- checking decompose() and reconstruct() for some/all generators on the level "
	   << level << ":" << endl;
      Index index(first_generator<Basis1D,2,Basis>(&basis, level));
      for (;; ++index)
	{
 	  InfiniteVector<double, Index> origcoeff;
 	  origcoeff[index] = 1.0;
	  
//  	  cout << "* original coeffs:" << endl << origcoeff;

 	  InfiniteVector<double, Index> wcoeff;
 	  basis.decompose(origcoeff, basis.j0(), wcoeff);
	  
//  	  cout << "* after decompose():" << endl << wcoeff;

 	  InfiniteVector<double, Index> transformcoeff;
 	  basis.reconstruct(wcoeff, level, transformcoeff);
	  
// 	  cout << "* after reconstruct():" << endl << transformcoeff;

 	  cout << "* generator: " << index
 	       << ", max. error: " << linfty_norm(origcoeff-transformcoeff) << endl;
	  
	  if (index == last_generator<Basis1D,2,Basis>(&basis, level)) break;
	}
    }
#endif
  
#if 0
  for (int level = basis.j0()+1; level <= basis.j0()+2; level++)
    {
      cout << "- checking decompose_t() and reconstruct_t() for some/all generators on the level "
	   << level << ":" << endl;
      Index index(first_generator<Basis1D,2,Basis>(&basis, level));
      for (;; ++index)
	{
	  InfiniteVector<double, Index> origcoeff;
	  origcoeff[index] = 1.0;
	  
	  InfiniteVector<double, Index> wcoeff;
	  basis.decompose_t(origcoeff, basis.j0(), wcoeff);
	  
	  InfiniteVector<double, Index> transformcoeff;
	  basis.reconstruct_t(wcoeff, level, transformcoeff);
	  
	  cout << "* generator: " << index
	       << ", max. error: " << linfty_norm(origcoeff-transformcoeff) << endl;
	  
	  if (index == last_generator<Basis1D,2,Basis>(&basis, level)) break;
	}
    }
#endif

#if 0
  cout << "- evaluating a primal generator..." << endl;
  Index lambda(first_generator<Basis1D,2,Basis>(&basis, basis.j0()));
  for (int i = 1; i <= 6; i++, ++lambda);
  cout << "  (lambda=" << lambda << " )" << endl;
  std::ofstream psistream("cube_wavelet.m");
  evaluate<Basis1D,2>(basis, lambda, true, 6).matlab_output(psistream);
  psistream.close();
  cout << "  ...done, see file cube_wavelet.m!" << endl;
  
  cout << "- evaluating a primal wavelet:" << endl;
  lambda = ++first_wavelet<Basis1D,2,Basis>(&basis, basis.j0());
  std::ofstream psistream2("cube_wavelet2.m");
  evaluate<Basis1D,2>(basis, lambda, true, 6).matlab_output(psistream2);
  psistream2.close();
  cout << "  ...done, see file cube_wavelet2.m!" << endl;
#endif

#if 0
  cout << "- evaluating a whole lot of primal generators/wavelets..." << endl;
  Index mu(basis.first_generator(basis.j0()));
  for (int i = 1; i <= 64; i++, ++mu) {
    cout << "  * mu=" << mu << endl;
    ostringstream os;
    os << "cube_wavelet_" << mu << ".m";
    ofstream psistream(os.str().c_str());
    evaluate<Basis1D,2>(basis, mu, true, 6).matlab_output(psistream);
    psistream.close();
  }
#endif
}