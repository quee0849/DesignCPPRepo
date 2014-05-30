//
//
//                      PathDependent.cpp
//
//

#include <PathDependent.h>

PathDependent::PathDependent(const MJArray& LookAtTimes_)
                        :   LookAtTimes(LookAtTimes_)
{}

const MJArray& PathDependent::GetLookAtTimes() const
{
    return LookAtTimes;
}

//Ex 7.5
//PayOffDifference::PayOffDifference(const Wrapper<PathDependent>& pathDepOption1, const Wrapper<PathDependent>& pathDepOption2, 
//								   PayOffBridge& ThePayOff_ )
//								:	Option1(pathDepOption1), 
//									Option2(pathDepOption2),
//                                    DeliveryTime(1.0),
//                                    ThePayOff(ThePayOff_),
//                                    NumberOfTimes(6)
//{
////	Option1 = pathDepOption1;
//	//Option2 = pathDepOption2;
//}
//
//unsigned long PayOffDifference::MaxNumberOfCashFlows() const
//{
//     return 1UL;
//}
//
//MJArray PayOffDifference::PossibleCashFlowTimes() const
//{
//    MJArray tmp(1UL);
//    tmp[0] = DeliveryTime;
//    return tmp;
//}
//
//unsigned long PayOffDifference::CashFlows(const MJArray& SpotValues, 
//                                    std::vector<CashFlow>& GeneratedFlows) const
//{ // need to take difference of generatedFlows from each option
//	double mean =1.0;// need to change
//    GeneratedFlows[0].TimeIndex = 0UL;
//    GeneratedFlows[0].Amount = ThePayOff(mean);
//
//    return 1UL;
//}
//
//PathDependent* PayOffDifference::clone() const
//{
//    return new PayOffDifference(*this);
//}


