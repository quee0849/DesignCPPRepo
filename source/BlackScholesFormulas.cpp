//
//
//                        BlackScholesFormulas.cpp
//
//


#include <BlackScholesFormulas.h>
#include <Normals.h>
#include <cmath>

#if !defined(_MSC_VER)
using namespace std;
#endif

double BlackScholesCall( double Spot,
                         double Strike,
                         double r,
                         double d,
                         double Vol,
                         double Expiry)
{
    double standardDeviation = Vol*sqrt(Expiry);
    double moneyness = log(Spot/Strike);
    double d1 =( moneyness +  (r-d)*Expiry+0.5* standardDeviation*standardDeviation)/standardDeviation;
    double d2 = d1 - standardDeviation;
    return Spot*exp(-d*Expiry) * CumulativeNormal(d1) - Strike*exp(-r*Expiry)*CumulativeNormal(d2);
}


double BlackScholesPut( double Spot,
                        double Strike,
                        double r,
                        double d,
                        double Vol,
                        double Expiry)
{
    double standardDeviation = Vol*sqrt(Expiry);
    double moneyness = log(Spot/Strike);
    double d1 =( moneyness +  (r-d)*Expiry+0.5* standardDeviation*standardDeviation)/standardDeviation;
    double d2 = d1 - standardDeviation;
    return Strike*exp(-r*Expiry)*(1.0-CumulativeNormal(d2)) - Spot*exp(-d*Expiry) * (1-CumulativeNormal(d1));
}

double BlackScholesDigitalCall( double Spot,
                                double Strike,
                                double r,
                                double d,
                                double Vol,
                                double Expiry)
{
    double standardDeviation = Vol*sqrt(Expiry);
    double moneyness = log(Spot/Strike);
    double d2 =( moneyness +  (r-d)*Expiry-0.5* standardDeviation*standardDeviation)/standardDeviation;
    return exp(-r*Expiry)*CumulativeNormal(d2);
}

double BlackScholesDigitalPut( double Spot,
                               double Strike,
                               double r,
                               double d,
                               double Vol,
                               double Expiry)
{
    double standardDeviation = Vol*sqrt(Expiry);
    double moneyness = log(Spot/Strike);
    double d2 =( moneyness +  (r-d)*Expiry-0.5* standardDeviation*standardDeviation)/standardDeviation;
    return exp(-r*Expiry)*(1.0-CumulativeNormal(d2));
}


double BlackScholesCallVega( double Spot,
                             double Strike,
                             double r,
                             double d,
                             double Vol,
                             double Expiry)
{
    double standardDeviation = Vol*sqrt(Expiry);
    double moneyness = log(Spot/Strike);
    double d1 =( moneyness +  (r-d)*Expiry+0.5* standardDeviation*standardDeviation)/standardDeviation; 
    return Spot*exp(-d*Expiry) * sqrt(Expiry)*NormalDensity(d1);
}

double BlackScholesForwardPrice( double Spot,
                             double Strike,
                             double r,
                             double d,
                             double Vol,
                             double Expiry)
{
    return exp(-r*Expiry)*(exp(r*Expiry-d*Expiry)*Spot-Strike);
}


double BlackScholesDigitalCallOption( double Spot,
                             double Strike,
                             double r,
                             double d,
                             double Vol,
                             double Expiry) {
    //double dplus = (log(S/K)+(r - d +sigma*sigma/2)*T)/(sigma*sqrt(T));
    const double dminus = (log(Spot/Strike)+(r-d  -Vol*Vol/2)*Expiry)/(Vol*sqrt(Expiry));
    return exp(-r*Expiry)*CumulativeNormal(dminus);
}

double BlackScholesDigitalPutOption( double Spot,
                             double Strike,
                             double r,
                             double d,
                             double Vol,
                             double Expiry) {
    const double dminus = (log(Spot/Strike)+(r-d-Vol*Vol/2)*Expiry)/(Vol*sqrt(Expiry));
    return exp(-r*Expiry)*CumulativeNormal(-dminus);
}

double BlackScholesZeroCouponBond( double Spot,
                             double Strike,
                             double r,
                             double d,
                             double Vol,
                             double Expiry){
    return exp(-r*Expiry);
}

double BlackScholesDelta( double Spot,
                         double Strike,
                         double r,
                         double d,
                         double Vol,
                         double Expiry) { // from http://en.wikipedia.org/wiki/Greeks_(finance)#Formulas_for_European_option_Greeks
							 double dplus=(log(Spot/Strike)+(r-d+Vol*Vol/2)*Expiry)/(Vol*sqrt(Expiry)); 
							 return exp(-Expiry*d)*CumulativeNormal(dplus);
}

double BlackScholesGamma( double Spot,
                         double Strike,
                         double r,
                         double d,
                         double Vol,
                         double Expiry) {
							 double dplus=(log(Spot/Strike)+(r-d+Vol*Vol/2)*Expiry)/(Vol*sqrt(Expiry)); 
							return exp(-Expiry*d)*NormalDensity(dplus)/(Spot*Vol*sqrt(Expiry));}

double BlackScholesVega( double Spot,
                         double Strike,
                         double r,
                         double d,
                         double Vol,
                         double Expiry) {
							const double dplus=(log(Spot/Strike)+(r-d+Vol*Vol/2)*Expiry)/(Vol*sqrt(Expiry)); 
							return Spot*exp(-Expiry*d)*NormalDensity(dplus)*sqrt(Expiry);}

double BlackScholesRho( double Spot,
                         double Strike,
                         double r,
                         double d,
                         double Vol,
                         double Expiry) {
							const double dminus=(log(Spot/Strike)+(r-d-Vol*Vol/2)*Expiry)/(Vol*sqrt(Expiry)); 
							return Strike*Expiry*exp(-Expiry*r)*CumulativeNormal(dminus);}


double BlackScholesTheta( double Spot,
                         double Strike,
                         double r,
                         double d,
                         double Vol,
						 double Expiry) {
const double dminus=(log(Spot/Strike)+(r-d-Vol*Vol/2)*Expiry)/(Vol*sqrt(Expiry));
const double dplus=(log(Spot/Strike)+(r-d+Vol*Vol/2)*Expiry)/(Vol*sqrt(Expiry));
return -exp(-d*Expiry)*Spot*NormalDensity(dplus)*Vol/(2*sqrt(Expiry)) 
       -r*Strike*exp(-r*Expiry)*CumulativeNormal(dminus)
	   +d*Spot*exp(-d*Expiry)*CumulativeNormal(dplus);
}

double BlackScholesDeltaFD( double Spot,
                         double Strike,
                         double r,
                         double d,
                         double Vol,
						 double Expiry, double epsilon) {
	return (BlackScholesCall(Spot + epsilon ,Strike,r,d,Vol,Expiry) -  BlackScholesCall(Spot ,Strike,r,d,Vol,Expiry))/epsilon;
}

double BlackScholesGammaFD( double Spot,
                         double Strike,
                         double r,
                         double d,
                         double Vol,
						 double Expiry, double epsilon) {
return (BlackScholesCall(Spot+epsilon,Strike,r,d,Vol,Expiry)-2*BlackScholesCall(Spot,Strike,r,d,Vol,Expiry)+BlackScholesCall(Spot-epsilon,Strike,r,d,Vol,Expiry))/(epsilon*epsilon);}

double BlackScholesVegaFD( double Spot,
                         double Strike,
                         double r,
                         double d,
                         double Vol,
						 double Expiry, double epsilon) { return (BlackScholesCall(Spot ,Strike,r,d,Vol+epsilon,Expiry) -  BlackScholesCall(Spot,Strike,r,d,Vol,Expiry))/epsilon;}

double BlackScholesRhoFD( double Spot,
                         double Strike,
                         double r,
                         double d,
                         double Vol,
						 double Expiry, double epsilon){
return (BlackScholesCall(Spot ,Strike,r+epsilon,d,Vol,Expiry)-BlackScholesCall(Spot,Strike,r,d,Vol,Expiry))/epsilon;
}


double BlackScholesThetaFD( double Spot,
                         double Strike,
                         double r,
                         double d,
                         double Vol,
						 double Expiry, double epsilon) { // theta is minus the T derivative
return -(BlackScholesCall(Spot ,Strike,r,d,Vol,Expiry+ epsilon)-BlackScholesCall(Spot,Strike,r,d,Vol,Expiry))/epsilon;
}


