//
//
//
//                      MCStatistics.cpp
//
//

#include<MCStatistics.h>
using namespace std;

StatisticsMean::StatisticsMean()
    :
    RunningSum(0.0), PathsDone(0UL)
{
}
    
void StatisticsMean::DumpOneResult(double result)
{
    PathsDone++;
    RunningSum += result;
}

vector<vector<double> > StatisticsMean::GetResultsSoFar() const
{
    vector<vector<double> > Results(1);

    Results[0].resize(1);
    Results[0][0] = RunningSum / PathsDone;

    return Results;
}

StatisticsMC* StatisticsMean::clone() const
{
    return new StatisticsMean(*this);
}

StatisticsBasic::StatisticsBasic()
    :
    RunningSum(0.0), PathsDone(0UL), RunningSumSquares(0.0)
{
}
    
void StatisticsBasic::DumpOneResult(double result)
{
    PathsDone++;
    RunningSum += result;
	RunningSumSquares += result*result;
}

vector<vector<double> > StatisticsBasic::GetResultsSoFar() const
{
    vector<vector<double> > Results(1);

    Results[0].resize(3);
	double mean=RunningSum/PathsDone;
	Results[0][0]=mean;
   double variance = RunningSumSquares / PathsDone - mean*mean; // variance
	Results[0][1]=variance;
   double stderror = sqrt(variance/PathsDone);
   	Results[0][2]=stderror;

    return Results;
}

StatisticsMC* StatisticsBasic::clone() const
{
    return new StatisticsBasic(*this);
}





