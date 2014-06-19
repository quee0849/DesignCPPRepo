//
//
//                      ExoticEngine.h
//
//

#ifndef EXOTIC_ENGINE_H
#define EXOTIC_ENGINE_H
#include <wrapper.h>
#include <Parameters.h>
#include <PathDependent.h>
#include <MCStatistics.h>
#include <vector>
// abstract base class for exotrics engine
class ExoticEngine
{
public:
	//constructor creates an engine that can do MC simulations given 
	// a smart pointer to a PathDependent option and given interest rates r. 
	//We need r here as this class handles the accounting for the cash flows. 
    ExoticEngine(const Wrapper<PathDependent>& TheProduct_,
                 const Parameters& r_);

	// GetOnePath is one part of two that makes up the main method of the class.
	// - this one is pure virtual and the defn in an inherited class will involve the choice of a model and 
	// stochastic process
    virtual void GetOnePath(MJArray& SpotValues)=0;
	// DoSimulation loops over all the NumberOfPaths paths -calling getOnePath to get the array of spot values then passing these values into DoOnePath to get the double value for that 
	// set of spot values (after discounting) - which is then recorded in the stats gatherer. 
    void DoSimulation(StatisticsMC& TheGatherer, unsigned long NumberOfPaths);
    virtual ~ExoticEngine(){}
	// 
	// 
	// DoOnePath is one part of two that makes up the main method of the class.
	// this one is concrete. This does everything necessary for one path given an array of spot values at times
	// t1, t2, ... tn
    double DoOnePath(const MJArray& SpotValues) const;

private:

    Wrapper<PathDependent> TheProduct;
    Parameters r;
	// this is an array of the discount factors e^{-\int_0^{tj} r dt } at each of the times t1, .. tn obtained from
	// TheProduct->PossibleCashFlowTimes()
    MJArray Discounts;
    mutable std::vector<CashFlow> TheseCashFlows;
};

#endif


