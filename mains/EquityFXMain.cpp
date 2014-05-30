//
//
//		EquityFXMain.cpp
//
//       
//
/*
    uses source files 
    AntiThetic.cpp
    Arrays.cpp,  
    ConvergenceTable.cpp, 
    ExoticBSEngine.cpp
    ExoticEngine
    MCStatistics.cpp
    Normals.cpp
    Parameters.cpp,
    ParkMiller.cpp,
    PathDependent.cpp
    PathDependentAsian.cpp
    PayOff3.cpp, 
    PayOffBridge.cpp,
    Random2.cpp,
  */
#include<ParkMiller.h>
#include<iostream>
using namespace std;
#include<MCStatistics.h>
#include<ConvergenceTable.h>
#include<AntiThetic.h>
#include<PathDependentAsian.h>
#include<ExoticBSEngine.h>
int main()
{

	double Expiry=1;
	double Strike=100; 
	double Spot=100; 
	double Vol=0.15; 
	double r=0.05;
    double d=0;
	
	unsigned long NumberOfPaths=1000000;
    unsigned NumberOfDates=6;
// for knock out rebates etc. Ex 7.2
	double RebateAmount = 5.0;
	double Barrier=90.0;

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

 //   cout << "\nd\n";
 //   cin >> d;

 //   cout << "Number of dates\n";
 //   cin >> NumberOfDates;

	//cout << "\nNumber of paths\n";
	//cin >> NumberOfPaths;

//cout << "\nEnter Barrier for Knockout\n";
	//cin >> Barrier;

	//cout << "\nEnter Rebate amount in event of knockout\n";
	//cin >> RebateAmount;



    PayOffCall thePayOff(Strike);


    MJArray times(NumberOfDates);

    for (unsigned long i=0; i < NumberOfDates; i++)
        times[i] = (i+1.0)*Expiry/NumberOfDates;

    ParametersConstant VolParam(Vol);
    ParametersConstant rParam(r);
    ParametersConstant dParam(d);
	//PathDependentGeometricAsian theOption(times, Expiry, thePayOff);
 //   PathDependentAsian theOption(times, Expiry, thePayOff);
	PathDependentDiscreteKnockout theOption(times, Expiry, RebateAmount,Barrier, thePayOff);
    StatisticsMean gatherer;
    ConvergenceTable gathererTwo(gatherer);

   
    RandomParkMiller generator(NumberOfDates);
    
    AntiThetic GenTwo(generator);

    ExoticBSEngine theEngine(theOption, rParam, dParam, VolParam, GenTwo, Spot);

    theEngine.DoSimulation(gathererTwo, NumberOfPaths);

    vector<vector<double> > results =gathererTwo.GetResultsSoFar();


	cout <<"\nFor the Asian call price the results are \n";
  
    {
    for (unsigned long i=0; i < results.size(); i++)
    {
        for (unsigned long j=0; j < results[i].size(); j++)
            cout << results[i][j] << " ";

        cout << "\n";
    }}

    double tmp;
    cin >> tmp;

	return 0;

}
