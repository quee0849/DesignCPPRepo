//
//
//                           PayOffFactory.h
//
//
#ifndef PAYOFF_FACTORY_H
#define PAYOFF_FACTORY_H
#include <PayOff3.h>

#if defined(_MSC_VER)
#pragma warning( disable : 4786)
#endif

#include <map>
#include <string>
#include <vector>
//uses the singleton pattern (could use the monostate pattern instead)
class PayOffFactory  
{
public:
// Note the typedef here allows us to refer to poiters to functions that take in a double and spit out a PayOff* as
	//  CreatePayOffFunction
	typedef PayOff* (*CreatePayOffFunction)(double[] );
	//typedef PayOff* (*CreatePayOffFunction)(double, double );
	//typedef PayOffMult* (*CreatePayOffFunction)(double );
	// This is a static method - we need it to be static so that it can be called without any objects of type PayOffFactory
	// existing -
	// also  - in the cpp file  we return a static local variable of type
	// PayOffFactory - using the static keyword in a different context here
	// - here it just makes sure that only one such instance of the return type is created.
    static PayOffFactory& Instance();
    void RegisterPayOff(std::string, CreatePayOffFunction);
	// note that PayOff* is type defed aboved
	// so i guess CreatePayOff returns a pointer to a payoff function.
    //PayOff* CreatePayOff(std::string PayOffId,double Strike, double SecondStrike=0.0);
	 PayOff* CreatePayOff(std::string PayOffId, double Strike[]);
	~PayOffFactory(){};

private:
	// this is a hash map that stores all registered payoffs as pairs of strings and
	// functions to create payoffs of that type.
    std::map<std::string, CreatePayOffFunction> TheCreatorFunctions;
	// make the constructors private so they can't be called. 
	// note that we have defined them and they do nothing -- so what?
	PayOffFactory(){}
	PayOffFactory(const PayOffFactory&){}
    PayOffFactory& operator=(const PayOffFactory&){ return *this;}

};

#endif 


