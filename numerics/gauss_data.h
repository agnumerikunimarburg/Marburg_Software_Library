// -*- c++ -*-

// +--------------------------------------------------------------------+
// | This file is part of MathTL - the Mathematical Template Library    |
// |                                                                    |
// | Copyright (c) 2002-2005                                            |
// | Thorsten Raasch                                                    |
// +--------------------------------------------------------------------+

#ifndef _MATHTL_GAUSS_DATA_H
#define _MATHTL_GAUSS_DATA_H

/*!
  Gauss(-Legendre) points and weights, computed up to machine accuracy
*/
static const double GaussPoints[][10] = {
  {+0.0},
  {-0.5773502691896258,  // -sqrt(3)/3
   +0.5773502691896258}, // +sqrt(3)/3
  {-0.7745966692414834,  // -sqrt(15)/5
   +0.0,
   +0.7745966692414834}, // +sqrt(15)/5
  {-0.8611363115940526,  // -sqrt(525+70*sqrt(30))/35
   -0.3399810435848563,  // -sqrt(525-70*sqrt(30))/35
   +0.3399810435848563,  // +sqrt(525-70*sqrt(30))/35
   +0.8611363115940526}, // +sqrt(525+70*sqrt(30))/35
  {-0.9061798459386640,  // -sqrt(245+14*sqrt(70))/21
   -0.5384693101056831,  // -sqrt(245-14*sqrt(70))/21
   +0.0,
   +0.5384693101056831,  // +sqrt(245-14*sqrt(70))/21
   +0.9061798459386640}, // +sqrt(245+14*sqrt(70))/21
  {-0.9324695142031520,  // from here on Maple-checked!
   -0.6612093864662645,  // (16 significant digits)
   -0.2386191860831972,
   +0.2386191860831972,
   +0.6612093864662645,
   +0.9324695142031520},
  {-0.9491079123427585,
   -0.7415311855993944,
   -0.4058451513773972,
   +0.0,
   +0.4058451513773972,
   +0.7415311855993944,
   +0.9491079123427585},
  {-0.9602898564975362,
   -0.7966664774136267,
   -0.5255324099163290,
   -0.1834346424956498,
   +0.1834346424956498,
   +0.5255324099163290,
   +0.7966664774136267,
   +0.9602898564975362},
  {-0.9681602395076261,
   -0.8360311073266358,
   -0.6133714327005904,
   -0.3242534234038089,
   +0.0,
   +0.3242534234038089,
   +0.6133714327005904,
   +0.8360311073266358,
   +0.9681602395076261},
  {-0.9739065285171717,
   -0.8650633666889845,
   -0.6794095682990244,
   -0.4333953941292472,
   -0.1488743389816312,
   +0.1488743389816312,
   +0.4333953941292472,
   +0.6794095682990244,
   +0.8650633666889845,
   +0.9739065285171717}
};

static const double GaussWeights[][10] = {
  {+1.0},
  {+0.5,
   +0.5},
  {+0.2777777777777778,     // 5/18
   +0.4444444444444444,     // 4/9
   +0.2777777777777778},    // 5/18
  {+0.1739274225687269,     // (3*sqrt(30)-5)*sqrt(30)/360
   +0.3260725774312731,     // (3*sqrt(30)+5)*sqrt(30)/360
   +0.3260725774312731,     // (3*sqrt(30)+5)*sqrt(30)/360
   +0.1739274225687269},    // (3*sqrt(30)-5)*sqrt(30)/360
  {+0.1184634425280945,     // 3*(7+5*sqrt(70))*sqrt(70)/200/(35+2*sqrt(70))
   +0.2393143352496832,     // 3*(-7+5*sqrt(70))*sqrt(70)/200/(35-2*sqrt(70))
   +0.2844444444444444,     // 64/225
   +0.2393143352496832,     // 3*(-7+5*sqrt(70))*sqrt(70)/200/(35-2*sqrt(70))
   +0.1184634425280945},    // 3*(7+5*sqrt(70))*sqrt(70)/200/(35+2*sqrt(70))
  {+0.8566224618958517e-1,  // from here on Maple-checked!
   +0.1803807865240693,     // (16 significant digits)
   +0.2339569672863455,
   +0.2339569672863455,
   +0.1803807865240693,
   +0.8566224618958517e-1},
  {+0.6474248308443485e-1,
   +0.1398526957446383,
   +0.1909150252525595,
   +0.2089795918367347,
   +0.1909150252525595,
   +0.1398526957446383,
   +0.6474248308443485e-1},
  {+0.5061426814518813e-1,
   +0.1111905172266872,
   +0.1568533229389436,
   +0.1813418916891810,
   +0.1813418916891810,
   +0.1568533229389436,
   +0.1111905172266872,
   +0.5061426814518813e-1},
  {+0.4063719418078721e-1,
   +0.9032408034742870e-1,
   +0.1303053482014677,
   +0.1561735385200014,
   +0.1651196775006299,
   +0.1561735385200014,
   +0.1303053482014677,
   +0.9032408034742870e-1,
   +0.4063719418078721e-1},
  {+0.3333567215434407e-1,
   +0.7472567457529030e-1,
   +0.1095431812579910,
   +0.1346333596549982,
   +0.1477621123573764,
   +0.1477621123573764,
   +0.1346333596549982,
   +0.1095431812579910,
   +0.7472567457529030e-1,
   +0.3333567215434407e-1}
};

#endif
