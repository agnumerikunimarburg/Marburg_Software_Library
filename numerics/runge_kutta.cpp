// implementation for runge_kutta.h

#include <utils/array1d.h>

namespace MathTL
{
  template <class VECTOR>
  ExplicitRungeKuttaScheme<VECTOR>::ExplicitRungeKuttaScheme(const Method method)
    : b()
  {
    switch(method) {
    case RK12:
      fsal = false;
      A = LowerTriangularMatrix<double>(2, 2, "0 1 0");
      b = Vector<double>(2, "1 0");
      bhat = Vector<double>(2, "0.5 0.5");
      c = Vector<double>(2, "0 1");
      break;
    case RK23:
      fsal = false;
      A = LowerTriangularMatrix<double>(3, 3, "0 0.5 0 -1 2 0");
      b = Vector<double>(3, "0 1 0");
      bhat.resize(3); bhat[0] = bhat[2] = 1./6; bhat[1] = 2./3;
      c = Vector<double>(3, "0 0.5 1");
      break;
    case Fehlberg34:
      fsal = true;
      A.resize(5,5);
      b.resize(5);
      bhat.resize(5);
      c.resize(5);
      A(1,0) = A(2,1) = 0.5;
      A(3,2) = 1.0;
      A(4,0) = A(4,3) = bhat[0] = bhat[3] = 1./6;
      A(4,1) = A(4,2) = bhat[1] = bhat[2] = 1./3;
      b[0] = b[4] = 1./6;
      b[1] = b[2] = 1./3;
      c[1] = c[2] = 0.5;
      c[3] = c[4] = 1.0;
      break;
    case DoPri45:
      fsal = true;
      A.resize(7,7);
      b.resize(7);
      bhat.resize(7);
      c.resize(7);
      A(1,0) = 1./5;
      A(2,0) = 3./40;
      A(2,1) = 9./40;
      A(3,0) = 44./45;
      A(3,1) = -56./15;
      A(3,2) = 32./9;
      A(4,0) = 19372./6561;
      A(4,1) = -25360./2187;
      A(4,2) = 64448./6561;
      A(4,3) = -212./729;
      A(5,0) = 9017./3168;
      A(5,1) = -355./33;
      A(5,2) = 46732./5247;
      A(5,3) = 49./176;
      A(5,4) = -5103./18656;
      A(6,0) = bhat[0] = 35./384;
      A(6,2) = bhat[2] = 500./1113;
      A(6,3) = bhat[3] = 125./192;
      A(6,4) = bhat[4] = -2187./6784;
      A(6,5) = bhat[5] = 11./84;
      b[0] = 5179./57600;
      b[2] = 7571./16695;
      b[3] = 393./640;
      b[4] = -92097./339200;
      b[5] = 187./2100;
      b[6] = 1./40;
      c[1] = 1./5;
      c[2] = 3./10;
      c[3] = 4./5;
      c[4] = 8./9;
      c[5] = c[6] = 1;
      break;
    case DoPri78:
      fsal = true;
      A.resize(13,13);
      b.resize(13);
      bhat.resize(13);
      c.resize(13);
      A(1,0) = 1./18;
      A(2,0) = 1./48;
      A(2,1) = 1./16;
      A(3,0) = 1./32;
      A(3,2) = 3./32;
      A(4,0) = 5./16;
      A(4,2) = -75./64;
      A(4,3) = 75./64;
      A(5,0) = 3./80;
      A(5,3) = 3./16;
      A(5,4) = 3./20;
      A(6,0) = 29443841./614563906.;
      A(6,3) = 77736538./692538347.;
      A(6,4) = -28693883./1125000000.;
      A(6,5) = 23124283./1800000000.;
      A(7,0) = 16016141./946692911.;
      A(7,3) = 61564180./158732637.;
      A(7,4) = 22789713./633445777.;
      A(7,5) = 545815736./2771057229.;
      A(7,6) = -180193667./1043307555.;
      A(8,0) = 39632708./573591083.;
      A(8,3) = -433636366./683701615.;
      A(8,4) = -421739975./2616292301.;
      A(8,5) = 100302831./723423059.;
      A(8,6) = 790204164./839813087.;
      A(8,7) = 800635310./3783071287.;
      A(9,0) = 246121993./1340847787.;
      A(9,3) = -37695042795./15268766246.;
      A(9,4) = -309121744./1061227803.;
      A(9,5) = -12992083./490766935.;
      A(9,6) = 6005943493./2108947869.;
      A(9,7) = 393006217./1396673457.;
      A(9,8) = 123872331./1001029789.;
      A(10,0) = -1028468189./846180014.;
      A(10,3) = 8478235783./508512852.;
      A(10,4) = 1311729495./1432422823.;
      A(10,5) = -10304129995./1701304382.;
      A(10,6) = -48777925059./3047939560.;
      A(10,7) = 15336726248./1032824649.;
      A(10,8) = -45442868181./3398467696.;
      A(10,9) = 3065993473./597172653.;
      A(11,0) = 185892177./718116043.;
      A(11,3) = -3185094517./667107341.;
      A(11,4) = -477755414./1098053517.;
      A(11,5) = -703635378./230739211.;
      A(11,6) = 5731566787./1027545527.;
      A(11,7) = 5232866602./850066563.;
      A(11,8) = -4093664535./808688257.;
      A(11,9) = 3962137247./1805957418.;
      A(11,10) = 65686358./487910083.;
      A(12,0) = 403863854./491063109.;
      A(12,3) = -5068492393./434740067.;
      A(12,4) = -411421997./543043805.;
      A(12,5) = 652783627./914296604.;
      A(12,6) = 11173962825./925320556.;
      A(12,7) = -13158990841./6184727034.;
      A(12,8) = 3936647629./1978049680.;
      A(12,9) = -160528059./685178525.;
      A(12,10) = 248638103./1413531060.;
      b[0] = 13451932./455176623.;
      b[5] = -808719846./976000145.;
      b[6] = 1757004468./5645159321.;
      b[7] = 656045339./265891186.;
      b[8] = -3867574721./1518517206.;
      b[9] = 465885868./322736535.;
      b[10] = 53011238./667516719.;
      b[11] = 2./45;
      bhat[0] = 14005451./335480064.;
      bhat[5] = -59238493./1068277825.;
      bhat[6] = 181606767./758867731.;
      bhat[7] = 561292985./797845732.;
      bhat[8] = -1041891430./1371343529.;
      bhat[9] = 760417239./1151165299.;
      bhat[10] = 118820643./751138087.;
      bhat[11] = -528747749./2220607170.;
      bhat[12] = 1./4;
      c[1] = 1./18;
      c[2] = 1./12;
      c[3] = 1./8;
      c[4] = 5./16;
      c[5] = 3./8;
      c[6] = 59./400;
      c[7] = 93./200;
      c[8] = 5490023248./9719169821.;
      c[9] = 13./20;
      c[10] = 1201146811./1299019798.;
      c[11] = c[12] = 1.;
      break;
    default:
      break;
    }
  }
  
  template <class VECTOR>
  void
  ExplicitRungeKuttaScheme<VECTOR>::increment(const AbstractIVP<VECTOR>* ivp,
					      const double t_m, const VECTOR& u_m,
					      const double tau,
					      VECTOR& u_mplus1,
					      VECTOR& error_estimate,
					      const double tolerance) const
  {
    const unsigned int stages = c.size(); // for readability

    Array1D<VECTOR> k(stages);
    k[0] = u_m; k[0] = 0; // to set the dimensiona correctly
    for (unsigned int i = 1; i < stages; i++)
      k[i] = k[0];

    VECTOR temp;

    // solve stage equations
    ivp->evaluate_f(t_m+c[0]*tau, u_m, tolerance/stages, k[0]);
    for (unsigned int i = 1; i < stages; i++) {
      temp = u_m;
      for (unsigned int j = 0; j < i; j++)
	temp.add(tau*A(i,j), k[j]);
      ivp->evaluate_f(t_m+c[i]*tau, temp, tolerance/stages, k[i]);
    }
    
    // solution at t_m+tau
    u_mplus1 = u_m;
    for (unsigned int i = 0; i < stages; i++)
      u_mplus1.add(tau*bhat[i], k[i]);

    // error estimate
    error_estimate = 0;
    for (unsigned int i = 0; i < stages; i++)
      error_estimate.add(tau*(bhat[i]-b[i]), k[i]);
  }
}
