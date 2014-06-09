//
//
//                  PayOffForward.cpp
//
//

#include <PayOffForward.h>

double PayOffForward::operator () (double Spot) const
{
    return Spot-Strike;
}

PayOffForward::PayOffForward(double Strike_) : Strike(Strike_)
{
}
//for ex 10.2
PayOffForward::PayOffForward(double Strikes_[]) : Strike(Strikes_[0])
{
}


PayOff* PayOffForward::clone() const
{
    return new PayOffForward(*this);
}




double PayOffDigitalCall::operator () (double Spot) const
{
	return (Spot>=Strike)?1:0;
}

PayOffDigitalCall::PayOffDigitalCall(double Strike_) : Strike(Strike_)
{
}
//for ex 10.2
PayOffDigitalCall::PayOffDigitalCall(double Strikes_[]) : Strike(Strikes_[0])
{
}


PayOff* PayOffDigitalCall::clone() const
{
    return new PayOffDigitalCall(*this);
}

// straight asset
double PayOffStock::operator () (double Spot) const
{
	return Spot;
}

PayOffStock::PayOffStock() 
{
}

PayOffStock::PayOffStock(double Strike_) 
{
}

PayOffStock::PayOffStock(double Strikes_[]) 
{
}


PayOff* PayOffStock::clone() const
{
    return new PayOffStock(*this);
}