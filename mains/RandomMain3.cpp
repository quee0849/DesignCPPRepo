//
//
//		RandomMain3.cpp
//
//       
//
/*
    uses source files 
    AntiThetic.cpp
    Arrays.cpp,  
    ConvergenceTable.cpp, 
    MCStatistics.cpp
    Normals.cpp
    Parameters.cpp,
    ParkMiller.cpp
    PayOff3.cpp, 
    PayOffBridge.cpp,
    Random2.cpp,
    SimpleMC8.cpp 
    Vanilla3.cpp, 
  */
#include<SimpleMC8.h>
#include<ParkMiller.h>
#include<iostream>
using namespace std;
#include<Vanilla3.h>
#include<MCStatistics.h>
#include<ConvergenceTable.h>
#include<AntiThetic.h>
#include "MersTwister.h"


int main()
{
	double Expiry=1;
	double Strike=100; 
	double Spot=100; 
	double Vol=0.15; 
	double r=0.05; 
	unsigned long NumberOfPaths =1000000;

	//cout << "\nEnter expiry\n";
	//cin >> Expiry;

	//cout << "\nStrike\n";
	//cin >> Strike;

	//cout << "\nEnter spot\n";
	//cin >> Spot;

	//cout << "\nEnter vol\n";
	//cin >> Vol;

	//cout << "\nr\n";
	//cin >> r;

	//cout << "\nNumber of paths\n";
	//cin >> NumberOfPaths;

    PayOffCall thePayOff(Strike);

    VanillaOption theOption(thePayOff, Expiry);

    ParametersConstant VolParam(Vol);
    ParametersConstant rParam(r);

    StatisticsMean gatherer;
    ConvergenceTable gathererTwo(gatherer);

    //RandomParkMiller generator(1);
	RandomMersTwister generator(1);
    AntiThetic GenTwo(generator);

	SimpleMonteCarlo6(theOption,
                                      Spot, 
                                      VolParam,
                                      rParam,
                                      NumberOfPaths,
                                      gathererTwo,
									  generator); // no Antithetic
                                      //GenTwo); // Antithetic

    vector<vector<double> > results =gathererTwo.GetResultsSoFar();

	cout <<"\nFor the call price the results are \n";
    for (unsigned long i=0; i < results.size(); i++)
    {
        for (unsigned long j=0; j < results[i].size(); j++)
            cout << results[i][j] << " ";

        cout << "\n";
    }
    double tmp;
    cin >> tmp;

	return 0;
}


