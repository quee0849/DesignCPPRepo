//                     ConvergenceTable.h
// ConvergenceTable inherits from StatisticsMC (the abstract base stats gathering class)
// so it has the same interface 
// and we can plug in a ConvergenceTable wherever we would plug in a statisticsMC
// like mean for example.
// It also contains a wrapped StatisticsMC object that contains all of the data. 
//

#ifndef CONVERGENCE_TABLE_H
#define CONVERGENCE_TABLE_H
#include <MCStatistics.h>
#include <wrapper.h>

class ConvergenceTable : public StatisticsMC
{
public:

    ConvergenceTable(const Wrapper<StatisticsMC>& Inner_);

    virtual StatisticsMC* clone() const;
    virtual void DumpOneResult(double result);
    virtual std::vector<std::vector<double> > GetResultsSoFar() const;

    
private:

    Wrapper<StatisticsMC> Inner;
    std::vector<std::vector<double> > ResultsSoFar;
    unsigned long StoppingPoint;
    unsigned long PathsDone;
};

#endif


