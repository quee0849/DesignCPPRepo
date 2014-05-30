//
//
//              BinomialTree.h
//
//


#pragma warning( disable : 4786 )


#include <TreeProducts.h>
#include <vector>
#include <Parameters.h>
#include <Arrays.h>
#include <cmath>
#include <iostream>


class SimpleBinomialTree
{

public:
	SimpleBinomialTree(double Spot_,
                       const Parameters& r_,
                       const Parameters& d_, 
                       double Volatility_,
                       unsigned long Steps,
                       double Time);
                  
// Here we input an option designed from Trees like TreeEuropean or TreeAmerican
	// I think most of the work is done here.
	double GetThePrice(const TreeProduct& TheProduct);

protected:

    void BuildTree(); 

private:
  
    double Spot;
    Parameters r;
	Parameters d;
    double Volatility;
    unsigned long Steps;
    double Time;
    bool TreeBuilt;

    std::vector<std::vector<std::pair<double, double> > > TheTree;
    MJArray Discounts;
};


//Ex 8.2

class BinomialTreeLinearMemory
{

public:
BinomialTreeLinearMemory(double Spot_,
                       const Parameters& r_,
                       const Parameters& d_, 
                       double Volatility_,
                       unsigned long Steps,
                       double Time);
                  
// Here we input an option designed from Trees like TreeEuropean or TreeAmerican
	// I think most of the work is done here.
	double GetThePrice(const TreeProduct& TheProduct);

protected:

    void BuildTree(); 

private:
  
    double Spot;
    Parameters r;
	Parameters d;
    double Volatility;
    unsigned long Steps;
    double Time;
    bool TreeBuilt;
// change this
    std::vector<std::vector<std::pair<double, double> > > TheTree;
	std::vector<std::pair<double, double>> TheTreeCurrentLevel;
	std::vector<std::pair<double, double>> TheTreeFutureLevel;
	std::vector<std::pair<double, double>> TheTreePreviousLevel;
    MJArray Discounts;
	//Enter spot values in the given vector of pairs which represents a single level of the
	// binomial tree. We use this as a helper function to populate the tree with spot vales
	void buildLevel(long currentLevelIndex, std::vector<std::pair<double,double> >& levelOfTree);
};
