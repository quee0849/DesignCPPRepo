//
//
//                  BSCallTwo.h
//
//
#ifndef BS_CALL_TWO_H
#define BS_CALL_TWO_H
#include <cmath>

class BSCallTwo
{

public:

    BSCallTwo(double r_, double d_,
                     double T, double Spot_,
                     double Strike_);

    double Price(double Vol) const;
    double Vega(double Vol) const;

private:

    double r;
    double d;
    double T;
    double Spot;
    double Strike;

};

class xToTheAlpha
{

public:

    xToTheAlpha(double alpha_);

    double Value(double x) const;
    double Derivative(double x) const;

private:
    const double alpha;

};

//for ex 9.1 define a new class where convergence is bad for Newton raphson



#endif



