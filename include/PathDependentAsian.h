//
//
//                  PathDependentAsian.h
//
//

#ifndef PATH_DEPENDENT_ASIAN_H
#define PATH_DEPENDENT_ASIAN_H

#include <PathDependent.h>
#include <PayOffBridge.h>
#include <cmath>
#include <BlackScholesFormulas.h>

class PathDependentAsian : public PathDependent
{
public:

    PathDependentAsian(const MJArray& LookAtTimes_, 
                       double DeliveryTime_,
                       const PayOffBridge& ThePayOff_);

    virtual unsigned long MaxNumberOfCashFlows() const;
    virtual MJArray PossibleCashFlowTimes() const;
    virtual unsigned long CashFlows(const MJArray& SpotValues, 
                                    std::vector<CashFlow>& GeneratedFlows) const;
    virtual ~PathDependentAsian(){}
    virtual PathDependent* clone() const;

private:

    double DeliveryTime;
    PayOffBridge ThePayOff;
    unsigned long NumberOfTimes;
};

// Ex 7.1
class PathDependentGeometricAsian : public PathDependent
{
public:

    PathDependentGeometricAsian(const MJArray& LookAtTimes_, 
                       double DeliveryTime_,
                       const PayOffBridge& ThePayOff_);

    virtual unsigned long MaxNumberOfCashFlows() const;
    virtual MJArray PossibleCashFlowTimes() const;
    virtual unsigned long CashFlows(const MJArray& SpotValues, 
                                    std::vector<CashFlow>& GeneratedFlows) const;
    virtual ~PathDependentGeometricAsian(){}
    virtual PathDependent* clone() const;

private:

    double DeliveryTime;
    PayOffBridge ThePayOff;
    unsigned long NumberOfTimes;
};

//Ex 7.2
class PathDependentDiscreteKnockout : public PathDependent
{
public:
	// constructor
    PathDependentDiscreteKnockout(const MJArray& LookAtTimes_, 
                       double DeliveryTime_, double Rebate_, double Barrier_,
                       const PayOffBridge& ThePayOff_);
	// returns the maximum number of cash flows - which should be 1 in this case
	// since the option is dead if we knockout
    virtual unsigned long MaxNumberOfCashFlows() const;
	// returns an array of possible cash flow times
    virtual MJArray PossibleCashFlowTimes() const;
	// input an array of spot values and a vector of cashflows
	// and we calculate the cash flows and write them into GeneratedFlows vector
	//what do we return?
	//Note that a CashFlow is just a class with two public fields - amount and time paid. 
    virtual unsigned long CashFlows(const MJArray& SpotValues, 
                                    std::vector<CashFlow>& GeneratedFlows) const;
	// destructor
    virtual ~PathDependentDiscreteKnockout(){}
	// "virtual copy constructor" clone method
    virtual PathDependent* clone() const;

private:

    double DeliveryTime;
	double Barrier;
	double Rebate;
    PayOffBridge ThePayOff;
    unsigned long NumberOfTimes;
};

//For Hedging Project 3.
class PathDependentDeltaHedge : public PathDependent
{
public:

    PathDependentDeltaHedge(const MJArray& LookAtTimes_, double r_, double d_, double vol_, double strike_,
                       double DeliveryTime_,
                       const PayOffBridge& ThePayOff_);

    virtual unsigned long MaxNumberOfCashFlows() const;
    virtual MJArray PossibleCashFlowTimes() const;
    virtual unsigned long CashFlows(const MJArray& SpotValues, 
                                    std::vector<CashFlow>& GeneratedFlows) const;
    virtual ~PathDependentDeltaHedge(){}
    virtual PathDependent* clone() const;

private:

    double DeliveryTime;
    PayOffBridge ThePayOff;
	double strike;
	double r; 
	double d;
	double vol;
	double expiry;
   // unsigned long NumberOfTimes; // dont actually need this as stored in MJArray LookAtTimes in base class. 
};

#endif
