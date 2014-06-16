//
//
//                      SimpleMC8.cpp
//                         
// This function contains an engine for randomly evolving the stock price from 
//S_0 to S_Expiry (= this Spot below)
#include<SimpleMC8.h>
#include <cmath>
#include <Arrays.h>

// the basic math functions should be in namespace std but aren't in VCPP6
#if !defined(_MSC_VER)
using namespace std;
#endif

void SimpleMonteCarlo6(const VanillaOption& TheOption, 
						 double Spot, 
						 const Parameters& Vol, 
						 const Parameters& r, 
                         unsigned long NumberOfPaths,
						 StatisticsMC& gatherer,
                         RandomBase& generator)
{
    generator.ResetDimensionality(1);

    double Expiry = TheOption.GetExpiry();
	double variance = Vol.IntegralSquare(0,Expiry);
	double rootVariance = sqrt(variance);
	double itoCorrection = -0.5*variance;
	double movedSpot = Spot*exp(r.Integral(0,Expiry) +itoCorrection);

	double thisSpot;
    double discounting = exp(-r.Integral(0,Expiry));

    MJArray VariateArray(1);

	for (unsigned long i=0; i < NumberOfPaths; i++)
	{
        generator.GetGaussians(VariateArray);
		thisSpot = movedSpot*exp( rootVariance*VariateArray[0]);
		double thisPayOff = TheOption.OptionPayOff(thisSpot);
        gatherer.DumpOneResult(thisPayOff*discounting);
	}

    return;
}
// Project 1 - Euler Stepping
void SimpleMonteCarlo7(const VanillaOption& TheOption, 
						 double Spot, 
						 const Parameters& Vol, 
						 const Parameters& r, 
                         unsigned long NumberOfPaths,
						 unsigned long NumberOfSteps,
						 StatisticsMC& gatherer,
                         RandomBase& generator)
{
    //generator.ResetDimensionality(1);
	generator.ResetDimensionality(NumberOfSteps);
    double Expiry = TheOption.GetExpiry();
	double deltaT = Expiry/NumberOfSteps;
	double variance = Vol.IntegralSquare(0,Expiry); // \sigma^2T
	double rootVariance = sqrt(variance/ NumberOfSteps); // \sigma \sqrt{Delta T}
	double rDeltaT= (r.Integral(0,Expiry)/Expiry)*deltaT; // this assumes r is constant. 
	//double itoCorrection = -0.5*variance; // -\sigma^2 T/2
	//double movedSpot = Spot*exp(r.Integral(0,Expiry) +itoCorrection);

	double thisSpot= Spot;
    double discounting = exp(-r.Integral(0,Expiry));

    MJArray VariateArray(NumberOfSteps);
	double nextSpot=0.0;

	for (unsigned long i=0; i < NumberOfPaths; i++)
	{	// I guess this method fills the MJArray with Gaussians
        generator.GetGaussians(VariateArray);
		thisSpot=Spot; //reset starting point for each path.
		for (unsigned long j= 0; j < NumberOfSteps; j++) 
		{
			nextSpot = thisSpot*(1 + rDeltaT + rootVariance*(VariateArray[j]));
			thisSpot=nextSpot;
		}
		double thisPayOff = TheOption.OptionPayOff(nextSpot);
        gatherer.DumpOneResult(thisPayOff*discounting);
	}

    return;
}


void SimpleMonteCarloForLRDelta(const VanillaOption& TheOption, 
						 double Spot, 
						 const Parameters& Vol, 
						 const Parameters& r, 
                         unsigned long NumberOfPaths,
						 StatisticsMC& gatherer,
                         RandomBase& generator)
{
    generator.ResetDimensionality(1);

    double Expiry = TheOption.GetExpiry();
	double variance = Vol.IntegralSquare(0,Expiry); // sigma^2T
	double rootVariance = sqrt(variance);
	double itoCorrection = -0.5*variance;
	double movedSpot = Spot*exp(r.Integral(0,Expiry) +itoCorrection);
	double averageR = r.Integral(0,Expiry);
	double subtractNumerator = averageR + itoCorrection; 


	double thisSpot;
    double discounting = exp(-r.Integral(0,Expiry));

    MJArray VariateArray(1);

	for (unsigned long i=0; i < NumberOfPaths; i++)
	{
        generator.GetGaussians(VariateArray);
		thisSpot = movedSpot*exp( rootVariance*VariateArray[0]);
		double thisPayOff = (TheOption.OptionPayOff(thisSpot))*(log(thisSpot/Spot) - subtractNumerator)/(Spot*variance);
        gatherer.DumpOneResult(thisPayOff*discounting); // payoff*Psi/Phi see (p. 195 of JoshiConcepts)
	}

    return;
}

