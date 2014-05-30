//
//
//                      TreeEuropean.cpp
//
//

#include <TreeEuropean.h>
#include <minmax.h>

TreeEuropean::TreeEuropean(double FinalTime,
                           const PayOffBridge& ThePayOff_)
                 : TreeProduct(FinalTime),
                   ThePayOff(ThePayOff_)
{
}

double TreeEuropean::FinalPayOff(double Spot) const
{
    return ThePayOff(Spot);
}

double TreeEuropean::PreFinalValue(double, //Spot, Borland compiler
                                 double, //Time,   doesnt like unused named variables
                                 double DiscountedFutureValue) const
{
    return DiscountedFutureValue;
}

TreeProduct* TreeEuropean::clone() const
{
    return new TreeEuropean(*this);
}
//
// Ex 8.1
//
//
//
//

TreeBarrier::TreeBarrier(double FinalTime,
                           const PayOffBridge& ThePayOff_, double Barrier_)
                 : TreeProduct(FinalTime),
                   ThePayOff(ThePayOff_),
				   Barrier(Barrier_)
{
}

double TreeBarrier::FinalPayOff(double Spot) const
{
    return ThePayOff(Spot);
}

double TreeBarrier::PreFinalValue(double Spot, //Borland compiler
                                 double, //Time,   doesnt like unused named variables
                                 double DiscountedFutureValue) const
{
	return (Spot <= Barrier) ? 0.0 : DiscountedFutureValue;
}

TreeProduct* TreeBarrier::clone() const
{
    return new TreeBarrier(*this);
}

