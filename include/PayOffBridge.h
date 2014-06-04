//                       PayOffBridge.h
//
//

#ifndef PAYOFFBRIDGE_H
#define PAYOFFBRIDGE_H

#include<PayOff3.h>

// this simply stores a pointer to an option payoff and takes care of memory management;
//see pg 54
// For vanilla options, we can then wrap this bridge in a VanillaOption class (see Vanilla3) - which will store Expiry
class PayOffBridge
{
public:

    PayOffBridge(const PayOffBridge& original);
    PayOffBridge(const PayOff& innerPayOff);

    inline double operator()(double Spot) const;
    ~PayOffBridge();
    PayOffBridge& operator=(const PayOffBridge& original);

private:

    PayOff* ThePayOffPtr;

};

inline double PayOffBridge::operator()(double Spot) const
{
    return ThePayOffPtr->operator ()(Spot);
}

#endif


