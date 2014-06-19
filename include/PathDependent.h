//
//
//                      PathDependent.h
//
//
//

#ifndef PATH_DEPENDENT_H
#define PATH_DEPENDENT_H
#include <Arrays.h>
#include <vector>
#include <wrapper.h>
#include <PayOffBridge.h>


//CashFlow class - this is really just a struct as all members are public
// just stores an amount and a Time index j (so that it is at tj = TheProduct->PossibleCashFlowTimes[TimeIndex] = tj)
class CashFlow
{
public:

    double Amount;
    unsigned long TimeIndex;
    // Note that CashFlow  has a default constructor so that we can create an STL vector of cashFlows
    CashFlow(unsigned long TimeIndex_=0UL, double Amount_=0.0) 
                : TimeIndex(TimeIndex_),
                  Amount(Amount_){};
 

};

// PathDependent (option): pure abstract base class for a path dependent option. This links up with ExoticEngine - for example the
// PossibleCashFlowTimes are passed to the exotic engine when the engine is constructed.
// we are using the template pattern here - we are just defining the interface and deferring the implementation of part of
// an algorithm to an inheritted class. 

class PathDependent
{
public:

    PathDependent(const MJArray& LookAtTimes);

    const MJArray& GetLookAtTimes() const;

    virtual unsigned long MaxNumberOfCashFlows() const=0;
	// these PossibleCashFlowTimes are passed to the exotic engine when the engine is constructed so 
	// that the discounting values can be precomputed. 
    virtual MJArray PossibleCashFlowTimes() const=0;
	//CashFlows is the main method of this class. We take in an array given the spot values for one path at times t1,.. ,tn
	// and we calculate the cashFlows from this and write then to a vector of CashFlows which is passed in by reference. 
	// This method is const i think because the vector of CashFlows is not part of our object and we therefore do not modify the PathDependent object in 
	// any way. 
	// It returns the number of CashFlows generated.
    virtual unsigned long CashFlows(const MJArray& SpotValues, 
                                    std::vector<CashFlow>& GeneratedFlows) const=0;
    virtual PathDependent* clone() const=0;

    virtual ~PathDependent(){}

private:

    MJArray LookAtTimes;

};
////Ex 7.5 (attempt)
//
//class PayOffDifference : public PathDependent {
//	
//	public:
//	PayOffDifference(const Wrapper<PathDependent>& pathDepOption1, const Wrapper<PathDependent>& pathDepOption2, 
//		PayOffBridge& ThePayOff_ );
//
////need to define this - will be sum of maxnumber of cash flows of two options
//    virtual unsigned long MaxNumberOfCashFlows() const;
//// need to define this - this will be the CashFlow Times of both options
//    virtual MJArray PossibleCashFlowTimes() const;
//	// need to define this - will write in +cash flows of option1 and - cash flows of option2
//    virtual unsigned long CashFlows(const MJArray& SpotValues, 
//                                    std::vector<CashFlow>& GeneratedFlows) const;
//    virtual ~PayOffDifference(){}
//    virtual PathDependent* clone() const;
//
//private:
//	Wrapper<PathDependent> Option1;
//	Wrapper<PathDependent> Option2;
//	PayOffBridge ThePayOff;
//    double DeliveryTime;
//    unsigned long NumberOfTimes;
//};



#endif


