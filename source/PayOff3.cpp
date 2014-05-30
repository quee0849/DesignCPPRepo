//
//
//                          PayOff3.cpp
//
//

#include <PayOff3.h>
#include <minmax.h>

PayOffCall::PayOffCall(double Strike_) : Strike(Strike_)
{
}
// extra
PayOffCall::PayOffCall(double Strikes_[]) : Strike(Strikes_[0])
{
}

double PayOffCall::operator () (double Spot) const
{
    return max(Spot-Strike,0.0);
}

PayOff* PayOffCall::clone() const
{
    return new PayOffCall(*this);
}
//PayOffPut

double PayOffPut::operator () (double Spot) const
{
    return max(Strike-Spot,0.0);
}

PayOffPut::PayOffPut(double Strike_) : Strike(Strike_)
{
}
PayOffPut::PayOffPut(double Strikes_[]) : Strike(Strikes_[0])
{
}

PayOff* PayOffPut::clone() const
{
    return new PayOffPut(*this);
}


//PayOffStraddle for Ex 10.1
double PayOffStraddle::operator () (double Spot) const
{
    return max(Strike-Spot,Spot-Strike); // payoff |S-K|
}

PayOffStraddle::PayOffStraddle(double Strike_) : Strike(Strike_)
{
}
//for ex 10.2
PayOffStraddle::PayOffStraddle(double Strikes_[]) : Strike(Strikes_[0])
{
}

PayOff* PayOffStraddle::clone() const
{
    return new PayOffStraddle(*this);
}