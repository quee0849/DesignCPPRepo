//
//
//                  payfactorymain.cpp
//
//
/*
Uses
    PayOff3.cpp
    PayOffBridge.cpp
    PayOffFactory.cpp
    PayOffRegistration.cpp

*/

#include <PayOff3.h>
#include <PayOffConstructible.h>
#include <PayOffBridge.h>
#include <PayOffFactory.h>
#include <string>
#include <iostream>
using namespace std;

int main()
{

    double Strike[1];
	Strike[0]=95;
	Strike[1]=105;
    std::string name;

    cout << "\npay-off name\n";
    cin >> name;

    cout << "Enter strike 1\n";
    cin >> Strike[0];
   
	cout << "Enter strike 2 (for double barrier for example)\n";
	cin >> Strike[1];



    PayOff* PayOffPtr = PayOffFactory::Instance().CreatePayOff(name,Strike); 

    if (PayOffPtr != NULL)
    {
        double Spot=106;

	    cout << "\nspot\n";
        cin >> Spot;

        cout << "\n PayOff with Spot " << Spot  << " is "<< PayOffPtr->operator ()(Spot) << "\n";    
        delete PayOffPtr;
    }
    
    double tmp;
    cin >> tmp;
    return 0;
}

