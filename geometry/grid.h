// -*- c++ -*-

// +--------------------------------------------------------------------+
// | This file is part of MathTL - the Mathematical Template Library    |
// |                                                                    |
// | Copyright (c) 2002-2004                                            |
// | Thorsten Raasch                                                    |
// +--------------------------------------------------------------------+

#ifndef _MATHTL_GRID_H
#define _MATHTL_GRID_H

#include <utils/array1d.h>
#include <algebra/matrix.h>

namespace MathTL
{
  /*!
    Abstract base class for n-dimensional rectangular grids in the
    style of Matlab. There, rectangular grids are the core ingredients for plotting
    functions from n-D to m-D.
    A 1-dimensional grid is just a vector x holding the mesh points.
    A 2-dimensional grid (a so-called quad-mesh) consists of 2 matrices x and y,
    holding the x- and y-coordinates of the mesh points.
    
    reference: Matlab/Octave help for the command 'surf'
   */
  template <unsigned int DIM>
  class Grid
  {
  public:
    /*!
      default constructor: empty grid
    */
    Grid();

    /*!
      Matlab output of the grid onto a stream
    */
    void matlab_output(std::ostream& os) const;
  };

  /*!
    specialization of Grid to one space dimension:
    1-dimensional grids are just vectors holding the mesh points.
  */
  template <>
  class Grid<1>
  {
  public:
    /*!
      default constructor: empty grid
    */
    Grid();

    /*!
      construct a 1D grid from an array of 1D points
    */
    Grid(const Array1D<double>& grid);

    /*!
      Matlab output of the grid onto a stream
    */
    void matlab_output(std::ostream& os) const;
    
  private:
    /*!
      internal storage for the grid points
    */
    Array1D<double> grid_;
  };

  /*!
    specialization of Grid to two space dimensions:
    2-dimensional grids (quad-meshes) consist of 2 matrices x and y,
    holding the x- and y-coordinates of the mesh points
  */
  template <>
  class Grid<2>
  {
  public:
    /*!
      default constructor: empty grid
    */
    Grid();

    /*!
      construct a 2D grid from two matrices 
    */
    Grid(const Matrix<double>& gridx, const Matrix<double>& gridy);

    /*!
      Matlab output of the grid onto a stream
    */
    void matlab_output(std::ostream& os) const;
    
  private:
    /*!
      internal storage for the grid points
      (a 2D array would be sufficient, but we don't have one...)
    */
    Matrix<double> gridx_, gridy_;
  };

}

// include implementation of inline functions
#include <geometry/grid.cpp>

#endif
