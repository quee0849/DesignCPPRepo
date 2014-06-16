//
//
//
//                SimpleMC8.h
//
//

#ifndef SIMPLEMC8_H
#define SIMPLEMC8_H

#include <Vanilla3.h>
#include <Parameters.h>
#include <Random2.h>
#include <MCStatistics.h>

void SimpleMonteCarlo6(const VanillaOption& TheOption, 
						 double Spot,
						 const Parameters& Vol, 
						 const Parameters& r,
                         unsigned long NumberOfPaths,
						 StatisticsMC& gatherer,
                         RandomBase& generator);
//using Euler stepping for Project 1
void SimpleMonteCarlo7(const VanillaOption& TheOption, 
						 double Spot, 
						 const Parameters& Vol, 
						 const Parameters& r, 
                         unsigned long NumberOfPaths, 
						 unsigned long NumberOfSteps,
						 StatisticsMC& gatherer,
                         RandomBase& generator);

// Monte Carlo method for calculating Delta by likelihood ratio method
void SimpleMonteCarloForLRDelta(const VanillaOption& TheOption, 
						 double Spot, 
						 const Parameters& Vol, 
						 const Parameters& r, 
                         unsigned long NumberOfPaths,
						 StatisticsMC& gatherer,
                         RandomBase& generator);

#endif


