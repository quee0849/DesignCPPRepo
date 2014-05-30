//
//
//                      BSCallTwo.cpp
//
//

#include <BSCallTwo.h>
#include <BlackScholesFormulas.h>

BSCallTwo::BSCallTwo(double r_, double d_,
                     double T_, double Spot_,
                     double Strike_)
                     :
                     r(r_),d(d_),
                     T(T_),Spot(Spot_),
                     Strike(Strike_)
{}

double BSCallTwo::Price(double Vol) const
{
    return BlackScholesCall(Spot,Strike,r,d,Vol,T);
}


double BSCallTwo::Vega(double Vol) const
{
    return BlackScholesCallVega(Spot,Strike,r,d,Vol,T);
}


xToTheAlpha::xToTheAlpha(double alpha_)
                     :
                     alpha(alpha_)
{}

double xToTheAlpha::Value(double x) const
{
    return pow(x,alpha);
}


double xToTheAlpha::Derivative(double x) const
{
    return alpha*pow(x, alpha-1);
}



