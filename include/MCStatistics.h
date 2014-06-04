//
//
//
//                      MCStatistics.h
//
//

#ifndef STATISTICS_H
#define STATISTICS_H

#include <vector>
// This is our  stats gatherting abstract base class that defines the interface 
// for for example StatisticsMean
class StatisticsMC
{
public:

    StatisticsMC(){}

    virtual void DumpOneResult(double result)=0; // pure virtual
    virtual std::vector<std::vector<double> > GetResultsSoFar() const=0;
	// have a virtual clone method to allow for virtual copy construction. (remember that constructors 
	// themselves cannot be virtual)
    virtual StatisticsMC* clone() const=0;
    virtual ~StatisticsMC(){}

private:

};

class StatisticsMean : public StatisticsMC
{
public:

    StatisticsMean();
    virtual void DumpOneResult(double result);
    virtual std::vector<std::vector<double> > GetResultsSoFar() const;
    virtual StatisticsMC* clone() const;

private:

    double RunningSum;
    unsigned long PathsDone;

};

// For project1

class StatisticsVariance : public StatisticsMC
{
public:

    StatisticsVariance();
    virtual void DumpOneResult(double result);
    virtual std::vector<std::vector<double> > GetResultsSoFar() const;
    virtual StatisticsMC* clone() const;

private:
	//double mean;
	double RunningSum;
    double RunningSumSquares;
    unsigned long PathsDone;
};

#endif
