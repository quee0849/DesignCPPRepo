//
//
//
//                          DoubleDigital.h
//
//                              

#ifndef DOUBLEDIGITAL_H
#define DOUBLEDIGITAL_H

#include <Payoff2.h>

class PayOffDoubleDigital : public PayOff
{
public:
    
    PayOffDoubleDigital(double LowerLevel_, double UpperLevel_);
    
    virtual double operator()(double Spot) const;
    virtual ~PayOffDoubleDigital(){}

private:

    double LowerLevel;
    double UpperLevel;


};

#endif



