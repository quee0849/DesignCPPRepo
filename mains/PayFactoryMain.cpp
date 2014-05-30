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

    double Strike=100;
    std::string name;

    //cout << "Enter strike\n";
    //cin >> Strike;
    
    cout << "\npay-off name\n";
    cin >> name;

    PayOff* PayOffPtr = PayOffFactory::Instance().CreatePayOff(name,Strike); 

    if (PayOffPtr != NULL)
    {
        double Spot=93;

 /*       cout << "\nspot\n";
        cin >> Spot;*/

        cout << "\n PayOff with Spot " << Spot << " and strike " << Strike << " is "<< PayOffPtr->operator ()(Spot) << "\n";    
        delete PayOffPtr;
    }
    
    double tmp;
    cin >> tmp;
    return 0;
}

