//
//
//	                	BinomialTree.cpp
//	
//

#include <BinomialTree.h>


// the basic math functions should be in namespace std but aren't in VCPP6
#if !defined(_MSC_VER)
using namespace std;
#endif

SimpleBinomialTree::SimpleBinomialTree(double Spot_,
									   const Parameters& r_,
									   const Parameters& d_,
									   double Volatility_,
                                       unsigned long Steps_,
                                       double Time_)
									   : Spot(Spot_), 
                                         r(r_),
                                         d(d_), 
                                         Volatility(Volatility_),
                                         Steps(Steps_),
                                         Time(Time_),
                                         Discounts(Steps)
{
    TreeBuilt=false;
}

void SimpleBinomialTree::BuildTree()
{    
    TreeBuilt = true;
    TheTree.resize(Steps+1);
    
    double InitialLogSpot = log(Spot);

    for (unsigned long i=0; i <=Steps; i++)
    {

        TheTree[i].resize(i+1);

        double thisTime = (i*Time)/Steps;

        double movedLogSpot = 
                            InitialLogSpot+ r.Integral(0.0, thisTime) 
                                          - d.Integral(0.0, thisTime);
    
        movedLogSpot -= 0.5*Volatility*Volatility*thisTime;

        double sd = Volatility*sqrt(Time/Steps);

        for (long j = -static_cast<long>(i), k=0; j <= static_cast<long>(i); j=j+2,k++)
              TheTree[i][k].first = exp(movedLogSpot+ j*sd);
    }
   
    for (unsigned long l=0; l <Steps; l++)
    {
        Discounts[l] = exp(- r.Integral(l*Time/Steps,(l+1)*Time/Steps));
    }
}

double SimpleBinomialTree::GetThePrice(const TreeProduct& TheProduct)
{
    if (!TreeBuilt)
        BuildTree();

    if (TheProduct.GetFinalTime() != Time)
        throw("mismatched product in SimpleBinomialTree");


    for (long j = -static_cast<long>(Steps), k=0; j <=static_cast<long>( Steps); j=j+2,k++)
        TheTree[Steps][k].second = TheProduct.FinalPayOff(TheTree[Steps][k].first);

	// i is the number of the levels of the tree
    for (unsigned long i=1; i <= Steps; i++)
    {
        unsigned long index = Steps-i;  
        double ThisTime = index*Time/Steps;
   //  j ranges over all the nodes at level index 
        for (long j = -static_cast<long>(index), k=0; j <= static_cast<long>(index); j=j+2,k++)
        {
            double Spot = TheTree[index][k].first;
			// futureDiscountedValue is just the value obtained from the formula on pg 20 of Rennie for backwards computing the value of the option
			// at each node on the tree
            double futureDiscountedValue = 
                            0.5*Discounts[index]*(TheTree[index+1][k].second+TheTree[index+1][k+1].second);
			//TheTree is a vector of vectors of pairs of doubles.

			// for a european option
			// this is the same as just doing TheTree[index][k].second = futureDiscountedValue;
			// futureDiscountedValue is the value of the option assuming it is kept alive
			// we now use PreFinalValue to possibly modify the value
			// for example in an american option we would change this value if early exercise had a higher value
			// and for a barrier option we would have to make the value 0 if we had breached the barrier. 
            TheTree[index][k].second = TheProduct.PreFinalValue(Spot,ThisTime,futureDiscountedValue); 
        }
        
    }
    return TheTree[0][0].second;
}

//Ex 8.2 
// idea is rather than to use a vector of vectors of pairs for TheTree, we just keep track of the 
// the current level and the previous level. 
// the simplebinomial tree first builds the tree and populates all the nodes with the stock price and
// then computes the price by working backwards through the tree. 



BinomialTreeLinearMemory::BinomialTreeLinearMemory(double Spot_,
									   const Parameters& r_,
									   const Parameters& d_,
									   double Volatility_,
                                       unsigned long Steps_,
                                       double Time_)
									   : Spot(Spot_), 
                                         r(r_),
                                         d(d_), 
                                         Volatility(Volatility_),
                                         Steps(Steps_),
                                         Time(Time_),
                                         Discounts(Steps),
										 TheTreeCurrentLevel(Steps_+1),
										 TheTreeFutureLevel(Steps_+1)
{
    TreeBuilt=false;
	TheTreeCurrentLevel.resize(5000);
	TheTreeFutureLevel.resize(5000);
	for (int j=0; j<5000; j++) {
		TheTreeCurrentLevel[j].first=0.0;
		TheTreeCurrentLevel[j].second=0.0;
		TheTreeFutureLevel[j].first=0.0;
		TheTreeFutureLevel[j].second=0.0;
	}
}

void BinomialTreeLinearMemory::BuildTree()
{    
    TreeBuilt = true;
}

void BinomialTreeLinearMemory::buildLevel(long currentLevelIndex, std::vector<std::pair<double,double> >& levelOfTree) {
	std::cout<< "Calling buildLevel wirh currentLevelIndex " << currentLevelIndex << std::endl; 
	double InitialLogSpot = log(Spot);
	double thisTime = (currentLevelIndex*Time)/Steps;
		// log S+r -d
        double movedLogSpot = 
                            InitialLogSpot+ r.Integral(0.0, thisTime) 
                                          - d.Integral(0.0, thisTime);
		//movedLogSpot  = logS +r -d - \sigma^2t/2
        movedLogSpot -= 0.5*Volatility*Volatility*thisTime;
		//sd = \sigma .sqrt(t/N)
        double sd = Volatility*sqrt(Time/Steps);
		//levelOfTree.resize(5000);
		// for loop over j and k with k starting from 0, j starting from -level; j going up by 2 at a timel k going up by 1 at a time
		for (long j = -currentLevelIndex, k=0; j <= currentLevelIndex; j=j+2,k++) {
			// for some reason we cant enter the last entry here???!!!!!!!!!!!!

 
			// set the node to be the stock price : Se^{(r-d-\sigma^2/2)t + \sigma W_t} 
			//see (8.3) on pg 121
			// j is the number of up moves
			//so we're actually using the formula at the top of p 123
			std::cout << "Entering with k  and  exp resp " << k << "  " <<  exp(movedLogSpot+ j*sd) << std::endl;
			(levelOfTree[k]).first = exp(movedLogSpot+ j*sd);

		}
    
}

double BinomialTreeLinearMemory::GetThePrice(const TreeProduct& TheProduct)
{
    if (!TreeBuilt)
        BuildTree();

    if (TheProduct.GetFinalTime() != Time)
        throw("mismatched product in SimpleBinomialTree");


   // calculate Discounts vector
    for (unsigned long l=0; l <=Steps; l++)
    {
        Discounts[l] = exp(- r.Integral(l*Time/Steps,(l+1)*Time/Steps));
    }
	//populate the bottom level of payoffs 
	// and also populate the FutureLevel spot prices
	//note that if there are N steps then there should be N+1 levels
	buildLevel(Steps, TheTreeFutureLevel);
	buildLevel(Steps-1, TheTreeCurrentLevel);
	for (long j = -static_cast<long>(Steps), k=0; j <=static_cast<long>(Steps); j=j+2,k++) {
		
		std::cout << "Populating bottom level with j (net number of up moves) ="<< j << " and k=" << k << "  "  <<  TheTreeFutureLevel[k].first << std::endl;
		//char c;
		//std::cin >> c; 
		TheTreeFutureLevel[k].second = TheProduct.FinalPayOff(TheTreeFutureLevel[k].first);
		std::cout << "Entered for TheTreeFutureLevel[k].second " << TheProduct.FinalPayOff(TheTreeFutureLevel[k].first) << std::endl;
	}

	// i is the number of the levels of the tree
    for (unsigned long i=0; i <= Steps; i++)
    {
	
        unsigned long index = Steps-i;  //so index starts at #Steps and goes down and finishes at 1
		buildLevel(index, TheTreeFutureLevel);
		buildLevel(index-1, TheTreeCurrentLevel);
        double ThisTime = index*Time/Steps;
	//  j ranges over all the nodes at level index 
        for (long j = -static_cast<long>(index-1), k=0; j <= static_cast<long>(index-1); j=j+2,k++) // changed to index-1
        {
            double Spot = TheTreeCurrentLevel[k].first;
			// futureDiscountedValue is just the value obtained from the formula on pg 20 of Rennie for backwards computing the value of the option
			// at each node on the tree
            double futureDiscountedValue = 
                            //0.5*Discounts[index]*(TheTreeFutureLevel[k].second+TheTreeFutureLevel[k+1].second);
							0.5*(TheTreeFutureLevel[k].second+TheTreeFutureLevel[k+1].second);
			// for a european option
			// this is the same as just doing TheTree[index][k].second = futureDiscountedValue;
			// futureDiscountedValue is the value of the option assuming it is kept alive
			// we now use PreFinalValue to possibly modify the value
			// for example in an american option we would change this value if early exercise had a higher value
			// and for a barrier option we would have to make the value 0 if we had breached the barrier. 
            TheTreeCurrentLevel[k].second = TheProduct.PreFinalValue(Spot,ThisTime,futureDiscountedValue); 
			std::cout << "index , k and TheTreeCurrentLevel[k].second are "<<  index <<" " << k <<" " << TheTreeCurrentLevel[k].second << std::endl;
        }    
    }
	//return 0.0;
    return TheTreeCurrentLevel[0].second; 
}