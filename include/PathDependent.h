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

class CashFlow
{
public:

    double Amount;
    unsigned long TimeIndex;
    
    CashFlow(unsigned long TimeIndex_=0UL, double Amount_=0.0) 
                : TimeIndex(TimeIndex_),
                  Amount(Amount_){};
 

};

class PathDependent
{
public:

    PathDependent(const MJArray& LookAtTimes);

    const MJArray& GetLookAtTimes() const;

    virtual unsigned long MaxNumberOfCashFlows() const=0;
    virtual MJArray PossibleCashFlowTimes() const=0;
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


