#include <iostream>
#include <interval/p_basis.h>

using namespace std;
using namespace WaveletTL;

int main()
{
  cout << "Testing wavelet bases from [P] ..." << endl;

  const int d = 3;
  const int dT = 5;

  typedef PBasis<d,dT> Basis;
  typedef Basis::Index Index;

//   Basis basis(0, 0); // no b.c.'s
//   Basis basis(1, 0); // complementary b.c. at x=0
//   Basis basis(0, 1); // complementary b.c. at x=1
  Basis basis(1, 1); // complementary b.c.'s

  cout << "- d=" << d << ", dT=" << dT << endl;
  cout << "- the (" << d << "," << dT << ") basis has j0=" << basis.j0() << endl;
  cout << "- the default wavelet index: " << Index() << endl;
  cout << "- leftmost generator on the coarsest level: " << first_generator(&basis, basis.j0()) << endl;
  cout << "- rightmost generator on the coarsest level: " << last_generator(&basis, basis.j0()) << endl;
  cout << "- leftmost wavelet on the coarsest level: " << first_wavelet(&basis, basis.j0()) << endl;
  cout << "- rightmost wavelet on the coarsest level: " << last_wavelet(&basis, basis.j0()) << endl;

#if 1
  cout << "- checking biorthogonality of Mj0, Mj0T for different levels:" << endl;
  for (int level = basis.j0(); level <= basis.j0()+2; level++)
    {
      SparseMatrix<double> mj0_t, mj0T;
      basis.assemble_Mj0_t(level, mj0_t);
      basis.assemble_Mj0T(level, mj0T);

      SparseMatrix<double> T = mj0_t * mj0T;
      for (unsigned int i = 0; i < T.row_dimension(); i++)
	T.set_entry(i, i, T.get_entry(i, i) - 1.0);
      cout << "* j=" << level << ",  ||Mj0^T*Mj0T-I||_infty: " << row_sum_norm(T) << endl;

      SparseMatrix<double> mj0, mj0T_t;
      basis.assemble_Mj0(level, mj0);
      basis.assemble_Mj0T_t(level, mj0T_t);

      T = mj0T_t * mj0;
      for (unsigned int i = 0; i < T.row_dimension(); i++)
	T.set_entry(i, i, T.get_entry(i, i) - 1.0);
      cout << "* j=" << level << ",  ||Mj0T^T*Mj0-I||_infty: " << row_sum_norm(T) << endl;
    }
#endif

#if 1
  cout << "- checking biorthogonality of Mj<->Gj and MjT<->GjT for different levels:" << endl;
  for (int level = basis.j0(); level <= basis.j0()+1; level++)
    {
      SparseMatrix<double> mj0, mj1;
      basis.assemble_Mj0(level, mj0);
      basis.assemble_Mj1(level, mj1);
      SparseMatrix<double> mj(mj0.row_dimension(), mj0.row_dimension());
      mj.set_block(0, 0, mj0);
      mj.set_block(0, mj0.column_dimension(), mj1);

      SparseMatrix<double> mj0T_t, mj1T_t;
      basis.assemble_Mj0T_t(level, mj0T_t);
      basis.assemble_Mj1T_t(level, mj1T_t);
      SparseMatrix<double> gj(mj0T_t.column_dimension(), mj0T_t.column_dimension());
      gj.set_block(0, 0, mj0T_t);
      gj.set_block(mj0T_t.row_dimension(), 0, mj1T_t);

      SparseMatrix<double> T = mj * gj;
      for (unsigned int i = 0; i < T.row_dimension(); i++)
	T.set_entry(i, i, T.get_entry(i, i) - 1.0);
      cout << "* j=" << level << ",  ||Mj*Gj-I||_infty: " << row_sum_norm(T) << endl;

      T = gj * mj;
      for (unsigned int i = 0; i < T.row_dimension(); i++)
	T.set_entry(i, i, T.get_entry(i, i) - 1.0);
      cout << "* j=" << level << ",  ||Gj*Mj-I||_infty: " << row_sum_norm(T) << endl;
      
      SparseMatrix<double> mj0T, mj1T;
      basis.assemble_Mj0T(level, mj0T);
      basis.assemble_Mj1T(level, mj1T);
      SparseMatrix<double> mjt(mj.row_dimension(), mj.row_dimension());
      mjt.set_block(0, 0, mj0T);
      mjt.set_block(0, mj0T.column_dimension(), mj1T);

      SparseMatrix<double> mj0_t, mj1_t;
      basis.assemble_Mj0_t(level, mj0_t);
      basis.assemble_Mj1_t(level, mj1_t);
      SparseMatrix<double> gjt(mj.row_dimension(), mj.row_dimension());
      gjt.set_block(0, 0, mj0_t);
      gjt.set_block(mj0_t.row_dimension(), 0, mj1_t);

      T = mjt * gjt;
      for (unsigned int i = 0; i < T.row_dimension(); i++)
	T.set_entry(i, i, T.get_entry(i, i) - 1.0);
      cout << "* j=" << level << ",  ||MjT*GjT-I||_infty: " << row_sum_norm(T) << endl;

      T = gjt * mjt;
      for (unsigned int i = 0; i < T.row_dimension(); i++)
	T.set_entry(i, i, T.get_entry(i, i) - 1.0);
      cout << "* j=" << level << ",  ||GjT*MjT-I||_infty: " << row_sum_norm(T) << endl;
    }
#endif

  return 0;
}
