//
//
//                  PayOffFactory.cpp: 
//
//
#if defined(_MSC_VER)
#pragma warning( disable : 4786)
#endif

#include <PayOffFactory.h>
#include <iostream>
using namespace std;

void PayOffFactory::RegisterPayOff(string PayOffId, CreatePayOffFunction CreatorFunction)
{
     TheCreatorFunctions.insert(pair<string,CreatePayOffFunction>(PayOffId,CreatorFunction));
}


// note PayOff* has been typedefed in the header file
// basicalled this function returns a function pointer to a function that creates payoffs given an input of strike
PayOff* PayOffFactory::CreatePayOff(string PayOffId, double Strike[])
//PayOff* PayOffFactory::CreatePayOff(string PayOffId, double Strike, double SecondStrike)
{
	// here we look up "call" for example in  the map TheCreatorFunctions 
	// so if "call" exists in the map then i points to the CreatePayOffFunction for calls
    map<string, CreatePayOffFunction>::const_iterator 
                                i = TheCreatorFunctions.find(PayOffId);
	
    if  (i == TheCreatorFunctions.end())
    {
		std::cout << PayOffId << " is an unknown payoff" << std::endl;
		return NULL;
	}
	// Now dereference
	return (i->second)(Strike);
	//return (i->second)(Strike,SecondStrike);
}

PayOffFactory& PayOffFactory::Instance()
{
    static PayOffFactory theFactory;
    return theFactory;
}


