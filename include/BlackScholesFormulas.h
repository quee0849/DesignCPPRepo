//
//
//                      BlackScholesFormulas.h
//
//

#ifndef BLACK_SCHOLES_FORMULAS_H
#define BLACK_SCHOLES_FORMULAS_H



double BlackScholesCall( double Spot,
                         double Strike,
                         double r,
                         double d,
                         double Vol,
                         double Expiry);


double BlackScholesPut( double Spot,
                        double Strike,
                        double r,
                        double d,
                        double Vol,
                        double Expiry);

double BlackScholesDigitalCall(double Spot,
                               double Strike,
                               double r,
                               double d,
                               double Vol,
                               double Expiry);


double BlackScholesCallVega( double Spot,
                             double Strike,
                             double r,
                             double d,
                             double Vol,
                             double Expiry);


double BlackScholesForward( double Spot,
                             double Strike,
                             double r,
                             double d,
                             double Vol,
                             double Expiry);

//Project B3
double BlackScholesForwardPrice( double Spot,
                             double Strike,
                             double r,
                             double d,
                             double Vol,
                             double Expiry);
double BlackScholesDigitalCall( double Spot,
                             double Strike,
                             double r,
                             double d,
                             double Vol,
                             double Expiry);
double BlackScholesDigitalPut( double Spot,
                             double Strike,
                             double r,
                             double d,
                             double Vol,
                             double Expiry);
double BlackScholesZeroCouponBond( double Spot,
                             double Strike,
                             double r,
                             double d,
                             double Vol,
                             double Expiry);


double BlackScholesDelta( double Spot,
                         double Strike,
                         double r,
                         double d,
                         double Vol,
                         double Expiry);


double BlackScholesGamma( double Spot,
                         double Strike,
                         double r,
                         double d,
                         double Vol,
                         double Expiry);

double BlackScholesVega( double Spot,
                         double Strike,
                         double r,
                         double d,
                         double Vol,
                         double Expiry);

double BlackScholesRho( double Spot,
                         double Strike,
                         double r,
                         double d,
                         double Vol,
                         double Expiry);


double BlackScholesTheta( double Spot,
                         double Strike,
                         double r,
                         double d,
                         double Vol,
                         double Expiry);

double BlackScholesDeltaFD( double Spot,
                         double Strike,
                         double r,
                         double d,
                         double Vol,
                         double Expiry,  double epsilon);

double BlackScholesGammaFD( double Spot,
                         double Strike,
                         double r,
                         double d,
                         double Vol,
                         double Expiry,  double epsilon);

double BlackScholesVegaFD( double Spot,
                         double Strike,
                         double r,
                         double d,
                         double Vol,
                         double Expiry,  double epsilon);

double BlackScholesRhoFD( double Spot,
                         double Strike,
                         double r,
                         double d,
                         double Vol,
                         double Expiry ,double epsilon);


double BlackScholesThetaFD( double Spot,
                         double Strike,
                         double r,
                         double d,
                         double Vol,
                         double Expiry, double epsilon);
#endif



