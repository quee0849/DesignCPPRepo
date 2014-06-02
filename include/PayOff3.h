//
//
//                            PayOff3.h
//
//

#ifndef PAYOFF3_H
#define PAYOFF3_H

class PayOff
{
public:

    PayOff(){};

    virtual double operator()(double Spot) const=0;
    virtual ~PayOff(){}
    virtual PayOff* clone() const=0;

private:
    
};

class PayOffCall : public PayOff
{
public:

    PayOffCall(double Strike_);
	PayOffCall(double Strikes_[]);

    virtual double operator()(double Spot) const;
    virtual ~PayOffCall(){}
    virtual PayOff* clone() const;

private:

    double Strike;

};


class PayOffPut : public PayOff
{
public:

    PayOffPut(double Strike_);
	// 
	PayOffPut(double Strikes_[]);
    virtual double operator()(double Spot) const;
    virtual ~PayOffPut(){}
    virtual PayOff* clone() const;

private:

    double Strike;

};
//Ex 10.1
// A straddle is the sum of a call and a put
// so it pays off |S-K|
class PayOffStraddle : public PayOff
{
public:

    PayOffStraddle(double Strike_);
	PayOffStraddle(double Strikes_[]);
    virtual double operator()(double Spot) const;
    virtual ~PayOffStraddle(){}
    virtual PayOff* clone() const;

private:

    double Strike;

};

#endif



