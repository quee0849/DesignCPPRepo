//
//
//                       PayOffConstructible.h
//
//

#ifndef PAYOFF_CONSTRUCTIBLE_H
#define PAYOFF_CONSTRUCTIBLE_H

#if defined(_MSC_VER)
#pragma warning( disable : 4786)
#endif

#include <iostream>
#include <PayOff3.h>
#include <PayOffForward.h>
#include <PayOffFactory.h>
#include <string>

// I guess PayOffHelper is our auxilliary class - one for each payoff class - that will register
// our payoff with the factory

template <class T>
class PayOffHelper
{
public:

    PayOffHelper(std::string);
	// Create is a member function that inputs a double - Strike - and returns a pointer to the payoff of type T
	// (PayOff is a base class) - taking advantage of polymorphism here.
    static PayOff* Create(double);
};

template <class T>
PayOff* PayOffHelper<T>::Create(double Strike)
{
	return new T(Strike);
}

// constructor 
template <class T>
PayOffHelper<T>::PayOffHelper(std::string id)
{
	PayOffFactory& thePayOffFactory = PayOffFactory::Instance(); //creates a factory if one does not already exist
    thePayOffFactory.RegisterPayOff(id,PayOffHelper<T>::Create); // registers the payoff
}	  

#endif 


