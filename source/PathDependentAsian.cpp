//
//
//
//                    PathDependentAsian.cpp
//
//

#include <PathDependentAsian.h>


PathDependentAsian::PathDependentAsian(const MJArray& LookAtTimes_, 
                                       double DeliveryTime_,
                                       const PayOffBridge& ThePayOff_)
                                       :
                                        PathDependent(LookAtTimes_),
                                        DeliveryTime(DeliveryTime_),
                                        ThePayOff(ThePayOff_),
                                        NumberOfTimes(LookAtTimes_.size())
{
}

unsigned long PathDependentAsian::MaxNumberOfCashFlows() const
{
     return 1UL;
}

MJArray PathDependentAsian::PossibleCashFlowTimes() const
{
    MJArray tmp(1UL);
    tmp[0] = DeliveryTime;
    return tmp;
}

unsigned long PathDependentAsian::CashFlows(const MJArray& SpotValues, 
                                    std::vector<CashFlow>& GeneratedFlows) const
{
    double sum = SpotValues.sum();
    double mean = sum/NumberOfTimes;

    GeneratedFlows[0].TimeIndex = 0UL;
    GeneratedFlows[0].Amount = ThePayOff(mean);

    return 1UL;
}

PathDependent* PathDependentAsian::clone() const
{
    return new PathDependentAsian(*this);
}


//Ex 7.1

PathDependentGeometricAsian::PathDependentGeometricAsian(const MJArray& LookAtTimes_, 
                                       double DeliveryTime_,
                                       const PayOffBridge& ThePayOff_)
                                       :
                                        PathDependent(LookAtTimes_),
                                        DeliveryTime(DeliveryTime_),
                                        ThePayOff(ThePayOff_),
                                        NumberOfTimes(LookAtTimes_.size())
{
}

unsigned long PathDependentGeometricAsian::MaxNumberOfCashFlows() const
{
     return 1UL;
}

MJArray PathDependentGeometricAsian::PossibleCashFlowTimes() const
{
	//
    MJArray tmp(1UL);
    tmp[0] = DeliveryTime;
    return tmp;
}

unsigned long PathDependentGeometricAsian::CashFlows(const MJArray& SpotValues, 
                                    std::vector<CashFlow>& GeneratedFlows) const
{

    double product = 1.0;
	double gMean=1.0;
	if (NumberOfTimes ==0) { gMean=0.0;}
	else {
		for (unsigned long j=0; j< NumberOfTimes ; j++) {
			gMean*=SpotValues[j]; 
			}
		gMean=std::pow(gMean,1.0/NumberOfTimes);
		}
  
    GeneratedFlows[0].TimeIndex = 0UL;
    GeneratedFlows[0].Amount = ThePayOff(gMean);

    return 1UL;
}

PathDependent* PathDependentGeometricAsian::clone() const
{
    return new PathDependentGeometricAsian(*this);
}


//Ex 7.2
//ok
PathDependentDiscreteKnockout::PathDependentDiscreteKnockout(const MJArray& LookAtTimes_, 
                                       double DeliveryTime_,  double Rebate_, double Barrier_,
                                       const PayOffBridge& ThePayOff_)
                                       :
                                        PathDependent(LookAtTimes_),
                                        DeliveryTime(DeliveryTime_),
										Rebate(Rebate_),
										Barrier(Barrier_),
                                        ThePayOff(ThePayOff_),
                                        NumberOfTimes(LookAtTimes_.size())
{
}

unsigned long PathDependentDiscreteKnockout::MaxNumberOfCashFlows() const
{ // think this should still be one - we either payout if we knock out and we are done
	// or we pay out (S-K)_+ at the end
     return 1UL;
}

MJArray PathDependentDiscreteKnockout::PossibleCashFlowTimes() const
{
	// needs to change to all the possible lookAt times
   // MJArray tmp(1UL);
    //tmp[0] = DeliveryTime;
    //return tmp;
	
	return GetLookAtTimes(); // from the base class pathdependent -
	// since we can pay out at any of the possible look at times. Technically we also need to add deliveryTime as the 
	// last possible cash flow time.
}

unsigned long PathDependentDiscreteKnockout::CashFlows(const MJArray& SpotValues, 
                                    std::vector<CashFlow>& GeneratedFlows) const
{
	//need to change this - to look at each spot value and see if it is less than the barrier and if so write the rebate
	// into the cash flow.
	for (unsigned long j=0; j< NumberOfTimes ; j++) {
		if (SpotValues[j] <= Barrier) {
			GeneratedFlows[0].Amount = Rebate; 
			GeneratedFlows[0].TimeIndex = j; 
			return 1UL; // exit since the option is dead if we knock out 
			} 
	}
   // if we get to this point, we did not knockout - so just calculate the payoff using the final spot value amount. 
    GeneratedFlows[0].TimeIndex = NumberOfTimes-1;
    GeneratedFlows[0].Amount = ThePayOff(SpotValues[NumberOfTimes-1]);

    return 1UL;
}

// ok
PathDependent* PathDependentDiscreteKnockout::clone() const
{
    return new PathDependentDiscreteKnockout(*this);
}



// PathDependetDeltaHedge
PathDependentDeltaHedge::PathDependentDeltaHedge(const MJArray& LookAtTimes_, double r_, double d_, double vol_, double strike_,
                                       double DeliveryTime_,
                                       const PayOffBridge& ThePayOff_)
                                       :
										r(r_), d(d_), vol(vol_), expiry(DeliveryTime_),// note we are assuming expiry and deliverty time are the same for now
                                        PathDependent(LookAtTimes_),
                                        DeliveryTime(DeliveryTime_),
                                        ThePayOff(ThePayOff_), strike(strike_)//,
                                     //   NumberOfTimes(LookAtTimes_.size())
{
}

unsigned long PathDependentDeltaHedge::MaxNumberOfCashFlows() const
{
     return GetLookAtTimes().size();
}
// just assuming expiry is 1 here for simplicity
// also assuming that the times are evenly spaced for now.
MJArray PathDependentDeltaHedge::PossibleCashFlowTimes() const
{
    return GetLookAtTimes();
}

unsigned long PathDependentDeltaHedge::CashFlows(const MJArray& SpotValues, 
                                    std::vector<CashFlow>& GeneratedFlows) const
{
	
    //double sum = SpotValues.sum();
    //double mean = sum/NumberOfTimes;
	unsigned long NumberOfTimes = MaxNumberOfCashFlows();
	GeneratedFlows[0].TimeIndex = 0;
	GeneratedFlows[0].Amount = BlackScholesDelta(SpotValues[0], strike, r,d, vol, expiry)*SpotValues[0]; //BlackScholesDelta(SpotValues[0], strike, r,d, vol, expiry)*SpotValues[0];
	for (unsigned long j=1; j< NumberOfTimes; j++)  {
		GeneratedFlows[j].TimeIndex = j;
		//double valueOfStockShouldHold=SpotValues[j]*BlackScholesDelta(SpotValues[j], strike, r,d, vol, expiry- GetLookAtTimes()[j]);
		GeneratedFlows[j].Amount= BlackScholesDelta(SpotValues[j], strike, r,d, vol, expiry - GetLookAtTimes()[j])*SpotValues[j]- SpotValues[j-1]*BlackScholesDelta(SpotValues[j-1], strike, r,d, vol, expiry - GetLookAtTimes()[j-1]);	
		// need to fix time vluae in delta
	}

    return NumberOfTimes;
}

PathDependent* PathDependentDeltaHedge::clone() const
{
    return new PathDependentDeltaHedge(*this);
}

