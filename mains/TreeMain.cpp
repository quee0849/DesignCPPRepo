//
//
//                      TreeMain.cpp
//
//
//      
/*
requires
    Arrays.cpp
    BinomialTree.cpp
    BlackScholesFormulas.cpp
    Normals.cpp
    Parameters.cpp
    PayOff3.cpp
    PayOffBridge.cpp
    PayOffForward.cpp
    TreeAmerican.cpp
    TreeEuropean.cpp
    TreeMain.cpp
    TreeProducts.cpp
  */
#include <BinomialTree.h>
#include <TreeAmerican.h>
#include <TreeEuropean.h>
#include <BlackScholesFormulas.h>
#include <PayOffForward.h>
#include <iostream>
using namespace std;
#include <cmath>
int main()
{
	double Expiry=1;
	double Strike=100; 
	double Spot=100; 
	double Vol=0.15; 
	double r=0.05;
    double d=0;
	unsigned long Steps=200;
	//for ex 8.1
	double Barrier=95.0;

	///*cout << "\nEnter expiry\n";
	//cin >> Expiry;

	//cout << "\nStrike\n";
	//cin >> Strike;

	//cout << "\nEnter spot\n";
	//cin >> Spot;

	//cout << "\nEnter vol\n";
	//cin >> Vol;

	//cout << "\nr\n";
	//cin >> r;

	//   cout << "\nd\n";
	//   cin >> d;

	//   cout << "\nNumber of steps\n";
	//cin >> Steps;*/

    PayOffPut thePayOff(Strike);

    ParametersConstant rParam(r);
    ParametersConstant dParam(d);

    TreeEuropean europeanOption(Expiry,thePayOff);
	//TreeBarrier europeanOption(Expiry,thePayOff,Barrier);
    TreeAmerican americanOption(Expiry,thePayOff);

    //BinomialTreeLinearMemory theTree(Spot,rParam,dParam,Vol,Steps,Expiry);//for Ex 8.2
	//SimpleBinomialTree theTree(Spot,rParam,dParam,Vol,Steps,Expiry);
	std::cout << "Using Trinomial tree model" << std::endl;
	TrinomialTree theTree(Spot,rParam,dParam,Vol,Steps,Expiry);// Ex 8.3
    double euroPrice = theTree.GetThePrice(europeanOption);
    double americanPrice = theTree.GetThePrice(americanOption);
    cout << "euro price " << euroPrice << " amer price " << americanPrice << "\n";
//was BlackScholesCall
    double BSPrice = BlackScholesPut(Spot,Strike,r,d,Vol,Expiry);
    cout << "BS formula euro price " << BSPrice << "\n";
    
    PayOffForward forwardPayOff(Strike);
    TreeEuropean forward(Expiry,forwardPayOff);

    double forwardPrice = theTree.GetThePrice(forward);
    cout << "forward price by tree " << forwardPrice << "\n";

    double actualForwardPrice = exp(-r*Expiry)*(Spot*exp((r-d)*Expiry)-Strike);
    cout << "forward price " << actualForwardPrice << "\n";

    Steps++; // now redo the trees with one more step
    SimpleBinomialTree theNewTree(Spot,rParam,dParam,Vol,Steps,Expiry);

    double euroNewPrice = theNewTree.GetThePrice(europeanOption);
    double americanNewPrice = theNewTree.GetThePrice(americanOption);

    cout << "euro new price " << euroNewPrice << " amer new price " << americanNewPrice << "\n";

    double forwardNewPrice = theNewTree.GetThePrice(forward);

    cout << "forward price by new tree " << forwardNewPrice << "\n";

    double averageEuro = 0.5*(euroPrice + euroNewPrice);
    double averageAmer = 0.5*(americanPrice + americanNewPrice);
    double averageForward = 0.5*(forwardPrice + forwardNewPrice);

    cout << "euro av price " << averageEuro << " amer av price " << averageAmer << "\n";
    cout << "av forward " << averageForward << "\n";

    double tmp;
    cin >> tmp;

	return 0;
}
